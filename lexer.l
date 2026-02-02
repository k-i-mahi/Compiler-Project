%{
/*
 * Linear Language Lexer
 * Author: Khadimul Islam Mahi (2107076)
 * 
 * This lexer tokenizes the Linear programming language
 * and outputs tokens in a format suitable for Bison parser.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Output file for tokens */
FILE *token_output;

/* Line number tracking */
int line_num = 1;

/* Token output function */
void write_token(const char* token_type, const char* value) {
    fprintf(token_output, "<%s, %s, line:%d>\n", token_type, value, line_num);
}

void write_token_int(const char* token_type, int value) {
    fprintf(token_output, "<%s, %d, line:%d>\n", token_type, value, line_num);
}

void write_token_float(const char* token_type, double value) {
    fprintf(token_output, "<%s, %f, line:%d>\n", token_type, value, line_num);
}

%}

/* Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          ({LETTER}|_)({LETTER}|{DIGIT}|_)*
INTEGER     {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+
STRING      \"([^\"\n]|\\.)*\"
CHAR        \'([^\'\n]|\\.)\'
WHITESPACE  [ \t]+
NEWLINE     \n
COMMENT     "//".*

%%

    /* ==================== KEYWORDS ==================== */

    /* Block delimiters */
"begin"         { write_token("KEYWORD", "BEGIN"); }
"end"           { write_token("KEYWORD", "END"); }

    /* Primitive Data Types */
"int"           { write_token("TYPE", "INT"); }
"float"         { write_token("TYPE", "FLOAT"); }
"bool"          { write_token("TYPE", "BOOL"); }
"char"          { write_token("TYPE", "CHAR"); }
"string"        { write_token("TYPE", "STRING"); }
"void"          { write_token("TYPE", "VOID"); }

    /* Custom Data Types */
"graph"         { write_token("TYPE", "GRAPH"); }
"tree"          { write_token("TYPE", "TREE"); }
"range_tree"    { write_token("TYPE", "RANGE_TREE"); }
"dsu"           { write_token("TYPE", "DSU"); }
"matrix"        { write_token("TYPE", "MATRIX"); }
"ordered_set"   { write_token("TYPE", "ORDERED_SET"); }

    /* Control Flow */
"if"            { write_token("KEYWORD", "IF"); }
"else"          { write_token("KEYWORD", "ELSE"); }
"while"         { write_token("KEYWORD", "WHILE"); }
"for"           { write_token("KEYWORD", "FOR"); }
"break"         { write_token("KEYWORD", "BREAK"); }
"continue"      { write_token("KEYWORD", "CONTINUE"); }
"return"        { write_token("KEYWORD", "RETURN"); }

    /* I/O */
"read"          { write_token("KEYWORD", "READ"); }
"print"         { write_token("KEYWORD", "PRINT"); }

    /* Function and Program Structure */
"func"          { write_token("KEYWORD", "FUNC"); }
"main"          { write_token("KEYWORD", "MAIN"); }
"const"         { write_token("KEYWORD", "CONST"); }

    /* Boolean Literals */
"true"          { write_token("BOOL_LITERAL", "TRUE"); }
"false"         { write_token("BOOL_LITERAL", "FALSE"); }
"null"          { write_token("KEYWORD", "NULL"); }

    /* Logical Operators (word form) */
"and"           { write_token("LOGICAL_OP", "AND"); }
"or"            { write_token("LOGICAL_OP", "OR"); }
"not"           { write_token("LOGICAL_OP", "NOT"); }

    /* ==================== CUSTOM FUNCTIONS (Mahi - 2107076) ==================== */
"mahi_sum"      { write_token("CUSTOM_FUNC", "MAHI_SUM"); }
"mahi_reverse"  { write_token("CUSTOM_FUNC", "MAHI_REVERSE"); }
"mahi_gcd"      { write_token("CUSTOM_FUNC", "MAHI_GCD"); }
"mahi_isprime"  { write_token("CUSTOM_FUNC", "MAHI_ISPRIME"); }

    /* ==================== OPERATORS ==================== */

    /* Arithmetic Operators */
"+"             { write_token("ARITH_OP", "PLUS"); }
"-"             { write_token("ARITH_OP", "MINUS"); }
"*"             { write_token("ARITH_OP", "MULTIPLY"); }
"/"             { write_token("ARITH_OP", "DIVIDE"); }
"%"             { write_token("ARITH_OP", "MODULO"); }

    /* Increment/Decrement */
"++"            { write_token("INC_DEC_OP", "INCREMENT"); }
"--"            { write_token("INC_DEC_OP", "DECREMENT"); }

    /* Assignment Operators */
"="             { write_token("ASSIGN_OP", "ASSIGN"); }
"+="            { write_token("ASSIGN_OP", "PLUS_ASSIGN"); }
"-="            { write_token("ASSIGN_OP", "MINUS_ASSIGN"); }
"*="            { write_token("ASSIGN_OP", "MULTIPLY_ASSIGN"); }
"/="            { write_token("ASSIGN_OP", "DIVIDE_ASSIGN"); }
"%="            { write_token("ASSIGN_OP", "MODULO_ASSIGN"); }

    /* Relational Operators */
"=="            { write_token("REL_OP", "EQUAL"); }
"!="            { write_token("REL_OP", "NOT_EQUAL"); }
"<="            { write_token("REL_OP", "LESS_EQUAL"); }
">="            { write_token("REL_OP", "GREATER_EQUAL"); }
"<"             { write_token("REL_OP", "LESS_THAN"); }
">"             { write_token("REL_OP", "GREATER_THAN"); }

    /* Logical Operators (symbol form) */
"&&"            { write_token("LOGICAL_OP", "LOGICAL_AND"); }
"||"            { write_token("LOGICAL_OP", "LOGICAL_OR"); }
"!"             { write_token("LOGICAL_OP", "LOGICAL_NOT"); }

    /* ==================== DELIMITERS ==================== */
"("             { write_token("DELIMITER", "LPAREN"); }
")"             { write_token("DELIMITER", "RPAREN"); }
"["             { write_token("DELIMITER", "LBRACKET"); }
"]"             { write_token("DELIMITER", "RBRACKET"); }
"{"             { write_token("DELIMITER", "LBRACE"); }
"}"             { write_token("DELIMITER", "RBRACE"); }
";"             { write_token("DELIMITER", "SEMICOLON"); }
","             { write_token("DELIMITER", "COMMA"); }
"."             { write_token("DELIMITER", "DOT"); }

    /* ==================== LITERALS ==================== */

{INTEGER}       { write_token_int("INT_LITERAL", atoi(yytext)); }
{FLOAT}         { write_token_float("FLOAT_LITERAL", atof(yytext)); }
{STRING}        { write_token("STRING_LITERAL", yytext); }
{CHAR}          { write_token("CHAR_LITERAL", yytext); }

    /* ==================== IDENTIFIERS ==================== */
{ID}            { write_token("IDENTIFIER", yytext); }

    /* ==================== WHITESPACE & COMMENTS ==================== */
{WHITESPACE}    { /* Ignore whitespace */ }
{NEWLINE}       { line_num++; }
{COMMENT}       { /* Ignore single-line comments */ }

    /* ==================== ERROR HANDLING ==================== */
.               { fprintf(stderr, "Error: Unrecognized character '%s' at line %d\n", yytext, line_num); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file> [output_file]\n", argv[0]);
        fprintf(stderr, "  input_file  : Linear source code file (.linear)\n");
        fprintf(stderr, "  output_file : Token output file (default: tokens.txt)\n");
        return 1;
    }
    
    /* Open input file */
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", argv[1]);
        return 1;
    }
    
    /* Set input to file */
    yyin = input_file;
    
    /* Open output file */
    const char *output_filename = (argc >= 3) ? argv[2] : "tokens.txt";
    token_output = fopen(output_filename, "w");
    if (!token_output) {
        fprintf(stderr, "Error: Cannot create output file '%s'\n", output_filename);
        fclose(input_file);
        return 1;
    }
    
    /* Write header */
    fprintf(token_output, "===========================================\n");
    fprintf(token_output, "  Linear Language Lexer Output\n");
    fprintf(token_output, "  Author: Khadimul Islam Mahi (2107076)\n");
    fprintf(token_output, "  Input File: %s\n", argv[1]);
    fprintf(token_output, "===========================================\n\n");
    fprintf(token_output, "TOKENS:\n");
    fprintf(token_output, "-------\n");
    
    /* Perform lexical analysis */
    yylex();
    
    /* Write footer */
    fprintf(token_output, "\n-------\n");
    fprintf(token_output, "Total lines processed: %d\n", line_num);
    fprintf(token_output, "===========================================\n");
    
    /* Cleanup */
    fclose(input_file);
    fclose(token_output);
    
    printf("Lexical analysis complete!\n");
    printf("Input:  %s\n", argv[1]);
    printf("Output: %s\n", output_filename);
    printf("Lines processed: %d\n", line_num);
    
    return 0;
}
