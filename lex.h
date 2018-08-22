/*
 * Definitions of lexemes and tokens
 *
 * Copyright (C) 2018 Nicolas Mauger
 * This file is subject to the terms and conditions of the
 * CeCILL free software license agreement. See the file
 * LICENSE in the main directory of T7 for more details.
 */

#define EOI       0 /* end of input */
#define SEMI      1 /* ; */
#define PLUS      2 /* + */
#define TIMES     3 /* * */
#define LP        4 /* ( */
#define RP        5 /* ) */
#define NUM_OR_ID 6 /*number or identifier */

extern char *yytext;
extern int   yyleng;
extern int   yylineno;

int  match(int token);
int  lex();
void advance();

