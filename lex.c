/*
 * A simple lexical analyzer
 *
 * Copyright (C) 2018 Nicolas Mauger
 * This file is subject to the terms and conditions of the
 * CeCILL free software license agreement. See the file
 * LICENSE in the main directory of T7 for more details.
 */

#include <stdio.h>
#include <ctype.h>

#include "lex.h"

char *yytext   = ""; /* Lexeme (not '\0' terminated */
int   yyleng   =  0; /* Lexeme length */
int   yylineno =  0; /* Input line number */

int lex()
{
    static char input_buffer[128];
    char *current;

    current = yytext + yyleng;

    while (1)
    {
        while (!*current)
        {
            /* Get new lines, skipping any leading white space on the line, until a nonblank line is found. */

            current = input_buffer;
            if ( !fgets (input_buffer, sizeof(input_buffer), stdin))
            {
                current = '\0';
                return EOI;
            }

            ++yylineno;

            while(isspace(*current)) ++current;
        }

        for ( ; *current ; ++current)
        {
            /* Get the next token */
            yytext = current;
            yyleng = 1;

            switch ( *current )
            {
            case EOF:
                return EOI ;
            case ';':
                return SEMI;
            case '+':
                return PLUS;
            case '*':
                return TIMES;
            case '(':
                return LP;
            case ')':
                return RP;

            case '\n':
            case '\t':
            case '\r':
            case  ' ':
                break;

            default:
                if (!isalnum(*current))
                {
                    fprintf(stderr, "Ignore illegal input <%c>\n", *current);
                }
                else
                {
                    while (isalnum(*current)) ++current;

                    yyleng = current - yytext;
                    return NUM_OR_ID;
                }

                break;
            }
        }
    }
}

static int Lookahead = -1; /* Lookahead token */

int match (int token )
{
    /* Return true if "token" matches the current lookahead symbol. */

    if (Lookahead == -1) Lookahead = lex();

    return token == Lookahead;

}

void advance()
{
    /* Advance the lookahead to the next input symbol. */

    Lookahead = lex();
}
