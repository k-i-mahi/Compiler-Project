%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "parser.tab.h"

// External yylval declaration from Bison
extern YYSTYPE yylval;

void yyerror(const char*);
%}

/* Flex options */
%option yylineno
%option noyywrap

/* Regular Expression Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INTEGER     {DIGIT}+|0[xX][0-9a-fA-F]+
FLOAT       {DIGIT}*"."{DIGIT}+|{DIGIT}+"."{DIGIT}*

%%
"/*"                    {
                            int c;
                            while ((c = input()) != 0) {
                                if (c == '*') {
                                    if ((c = input()) == '/') {
                                        break;
                                    } else {
                                        unput(c);
                                    }
                                }
                            }
                        }
"//".*                  { }

[ \t\r]+                { }
\n                      { }

"START"                 { return T_START; }
"END"                   { return T_END; }
"main"                  { return T_MAIN; }
"function"              { return T_FUNCTION; }

"int"                   { yylval.type_val = TYPE_INT; return T_INT; }
"float"                 { yylval.type_val = TYPE_FLOAT; return T_FLOAT; }
"bool"                  { yylval.type_val = TYPE_BOOL; return T_BOOL; }
"char"                  { yylval.type_val = TYPE_CHAR; return T_CHAR; }
"string"                { yylval.type_val = TYPE_STRING; return T_STRING; }
"void"                  { yylval.type_val = TYPE_VOID; return T_VOID; }
"Graph"                 { yylval.type_val = TYPE_GRAPH; return T_GRAPH; }
"Tree"                  { yylval.type_val = TYPE_TREE; return T_TREE; }
"RangeTree"             { yylval.type_val = TYPE_RANGE_TREE; return T_RANGE_TREE; }
"DSU"                   { yylval.type_val = TYPE_DSU; return T_DSU; }
"Matrix"                { yylval.type_val = TYPE_MATRIX; return T_MATRIX; }
"OrderedSet"            { yylval.type_val = TYPE_ORDERED_SET; return T_ORDERED_SET; }
"Stack"                 { yylval.type_val = TYPE_STACK; return T_STACK; }
"Queue"                 { yylval.type_val = TYPE_QUEUE; return T_QUEUE; }

"if"                    { return T_IF; }
"else"                  { return T_ELSE; }
"for"                   { return T_FOR; }
"while"                 { return T_WHILE; }
"return"                { return T_RETURN; }
"break"                 { return T_BREAK; }
"continue"              { return T_CONTINUE; }

"true"                  { yylval.int_val = 1; return T_BOOL_LITERAL; }
"false"                 { yylval.int_val = 0; return T_BOOL_LITERAL; }
{INTEGER}               {
                            if (yytext[0] == '0' && (yytext[1] == 'x' || yytext[1] == 'X'))
                                yylval.int_val = (int)strtol(yytext, NULL, 0);
                            else
                                yylval.int_val = atoi(yytext);
                            return T_INT_LITERAL;
                        }
{FLOAT}                 { yylval.float_val = atof(yytext); return T_FLOAT_LITERAL; }
\"(\\.|[^\"])*\"        { yylval.str_val = strdup(yytext); return T_STRING_LITERAL; }
'([^'\\]|\\.)'          { yylval.str_val = strdup(yytext); return T_CHAR_LITERAL; }

"MAHI_read"             { return T_MAHI_READ; }
"MAHI_write"            { return T_MAHI_WRITE; }
"MAHI_sort"             { return T_MAHI_SORT; }
"MAHI_push"             { return T_MAHI_PUSH; }

"="                     { return T_ASSIGN; }
"+="                    { return T_PLUS_ASSIGN; }
"-="                    { return T_MINUS_ASSIGN; }
"*="                    { return T_STAR_ASSIGN; }
"/="                    { return T_SLASH_ASSIGN; }
"%="                    { return T_PERCENT_ASSIGN; }
"+"                     { return T_PLUS; }
"-"                     { return T_MINUS; }
"*"                     { return T_MULTIPLY; }
"/"                     { return T_DIVIDE; }
"%"                     { return T_MODULO; }
"=="                    { return T_EQ; }
"!="                    { return T_NEQ; }
"<"                     { return T_LT; }
">"                     { return T_GT; }
"<="                    { return T_LTE; }
">="                    { return T_GTE; }
"&&"                    { return T_AND; }
"||"                    { return T_OR; }
"!"                     { return T_NOT; }

"("                     { return T_LPAREN; }
")"                     { return T_RPAREN; }
"{"                     { return T_LBRACE; }
"}"                     { return T_RBRACE; }
"["                     { return T_LBRACKET; }
"]"                     { return T_RBRACKET; }
";"                     { return T_SEMICOLON; }
","                     { return T_COMMA; }

{ID}                    { yylval.str_val = strdup(yytext); return T_IDENTIFIER; }

.                       { yyerror("Invalid character"); }

%%
