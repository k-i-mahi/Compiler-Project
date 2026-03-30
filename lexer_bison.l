%{
/*
 * Linear Language Lexer (Bison Integration)
 * Author: Khadimul Islam Mahi (2107076)
 * Course: Compiler Design Laboratory
 * 
 * This lexer returns tokens to Bison parser for syntax analysis.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"  /* Token definitions from Bison */

/* Track line numbers for error reporting */
int yylineno = 1;

%}

/* Options */
%option noyywrap

/* ==================== REGULAR EXPRESSION DEFINITIONS ==================== */

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          ({LETTER}|_)({LETTER}|{DIGIT}|_)*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+
STRING      \"([^\"\n]|\\.)*\"
CHAR        \'([^\'\n]|\\.)*\'
WHITESPACE  [ \t]+
NEWLINE     \n
COMMENT     "//".*

%%

    /* ==================== KEYWORDS ==================== */

"begin"         { return BEGIN_TOKEN; }
"end"           { return END_TOKEN; }

    /* Primitive Data Types */
"int"           { return INT; }
"float"         { return FLOAT; }
"bool"          { return BOOL; }
"char"          { return CHAR; }
"string"        { return STRING; }
"void"          { return VOID; }

    /* Custom Data Types */
"graph"         { return GRAPH; }
"tree"          { return TREE; }
"range_tree"    { return RANGE_TREE; }
"dsu"           { return DSU; }
"matrix"        { return MATRIX; }
"ordered_set"   { return ORDERED_SET; }

    /* Control Flow */
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"return"        { return RETURN; }

    /* I/O */
"read"          { return READ; }
"print"         { return PRINT; }

    /* Function and Program Structure */
"func"          { return FUNC; }
"main"          { return MAIN; }
"const"         { return CONST; }

    /* Boolean Literals and Null */
"true"          { return TRUE_LITERAL; }
"false"         { return FALSE_LITERAL; }
"null"          { return NULL_TOKEN; }

    /* Logical Operators (word form) */
"and"           { return AND; }
"or"            { return OR; }
"not"           { return NOT; }

    /* ==================== CUSTOM FUNCTIONS (Mahi - 2107076) ==================== */

"mahi_sum"      { return MAHI_SUM; }
"mahi_reverse"  { return MAHI_REVERSE; }
"mahi_gcd"      { return MAHI_GCD; }
"mahi_isprime"  { return MAHI_ISPRIME; }

    /* ==================== OPERATORS ==================== */

    /* Increment/Decrement - must be before + and - */
"++"            { return INCREMENT; }
"--"            { return DECREMENT; }

    /* Compound Assignment - must be before simple = */
"+="            { return PLUS_ASSIGN; }
"-="            { return MINUS_ASSIGN; }
"*="            { return MULTIPLY_ASSIGN; }
"/="            { return DIVIDE_ASSIGN; }
"%="            { return MODULO_ASSIGN; }

    /* Relational Operators - multi-char first */
"=="            { return EQUAL; }
"!="            { return NOT_EQUAL; }
"<="            { return LESS_EQUAL; }
">="            { return GREATER_EQUAL; }

    /* Logical Operators (symbol form) */
"&&"            { return LOGICAL_AND; }
"||"            { return LOGICAL_OR; }

    /* Single-character operators */
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"%"             { return MODULO; }
"="             { return ASSIGN; }
"<"             { return LESS_THAN; }
">"             { return GREATER_THAN; }
"!"             { return LOGICAL_NOT; }

    /* ==================== DELIMITERS ==================== */

"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
";"             { return SEMICOLON; }
","             { return COMMA; }
"."             { return DOT; }

    /* ==================== LITERALS ==================== */

{INTEGER}       { yylval.int_val = atoi(yytext); return INT_LITERAL; }
{FLOAT}         { yylval.float_val = atof(yytext); return FLOAT_LITERAL; }
{STRING}        { yylval.str_val = strdup(yytext); return STRING_LITERAL; }
{CHAR}          { yylval.char_val = yytext[1]; return CHAR_LITERAL; }

    /* ==================== IDENTIFIERS ==================== */

{ID}            { yylval.str_val = strdup(yytext); return IDENTIFIER; }

    /* ==================== WHITESPACE & COMMENTS ==================== */

{WHITESPACE}    { /* Ignore */ }
{NEWLINE}       { yylineno++; }
{COMMENT}       { /* Ignore single-line comments */ }

    /* ==================== ERROR HANDLING ==================== */

.               { 
                    fprintf(stderr, "Lexical Error at line %d: Unrecognized character '%s'\n", 
                            yylineno, yytext); 
                }

%%
