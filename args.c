/*
 * Code generation using subroutine arguments
 *
 * Copyright (C) 2018 Nicolas Mauger
 * This file is subject to the terms and conditions of the
 * CeCILL free software license agreement. See the file
 * LICENSE in the main directory of T7 for more details.
 */

#include <stdio.h>

#include "lex.h"

void expression (char *tempvar ) ;
void factor     (char *tempvar ) ;
void term       (char *tempvar ) ;

extern char *newname (void ) ;
extern void freename (char *name);

void statements(char *tempvar)
{
    /* statements -> expression SEMI | expression SEMI statements */

    while (!match(EOI))
    {
        expression(tempvar = newname());
        freename(tempvar);

        if (match(SEMI)) advance();
        else
        {
            fprintf(stderr, "%d: Inserting missing semicolon\n", yylineno);
        }
    }
}

void expression(char *tempvar)
{
    /* expression  -> term expression'
     * expression' -> PLUS term expression' | epsilon
     */

    char *tempvar2;
    term(tempvar);

    while (match(PLUS))
    {
        advance();

        term(tempvar2 = newname());

        printf("    %s += %s\n", tempvar, tempvar2);
        freename(tempvar2);
    }
}

void term(char *tempvar)
{

    char *tempvar2;

    factor(tempvar);

    while (match(TIMES))
    {
        advance();
        factor(tempvar2 = newname());
        printf("    %s *= %s\n", tempvar, tempvar2);
        freename(tempvar2);
    }
}

void factor(char *tempvar)
{
    if (match(NUM_OR_ID))
    {
        printf("    %s = %-*s\n", tempvar, yyleng, yytext);
        advance();
    }
    else if (match(LP))
    {
        advance();
        expression(tempvar);

        if (match(RP)) advance();
        else
        {
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
        }
    }
    else
    {
        fprintf(stderr, "%d: Number or identifier expected\n", yylineno);
    }
}
