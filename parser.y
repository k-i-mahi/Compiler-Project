/*
 * Bison Parser for Linear Language
 * Author: Khadimul Islam Mahi (2107076)
 *
 * This file defines the context-free grammar for the Linear language
 * and will be used by Bison to generate the parser.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
#include "symbol_table.h"
#include "ast.h"
#include "eval.h"
#include "tac_gen.h"
#include "c_gen.h"

// External declarations
extern int yylex();
extern int yylineno;
extern char* yytext;
void yyerror(const char *s);
static void insert_param_symbols(ASTNode *params);
static int generate_token_file(const char *source_path, char *out_path, size_t out_path_size);
static const char *token_name(int tok);
static void free_token_payload_if_needed(int tok);

ASTNode* root = NULL; // The root of the abstract syntax tree
%}

/* === Bison Union for Token Values === */
// This union holds the different types of data our tokens can have.
%union {
    int int_val;
    float float_val;
    char* str_val;
    DataType type_val; // To hold type information
    struct ASTNode* ast; // AST node pointers
}

/* === Token Declarations === */

// Keywords for data types
%token <type_val> T_INT T_FLOAT T_BOOL T_CHAR T_STRING T_VOID
%token <type_val> T_GRAPH T_TREE T_RANGE_TREE T_DSU T_MATRIX T_ORDERED_SET T_STACK T_QUEUE

// Keywords for control flow
%token T_IF T_ELSE T_FOR T_WHILE T_RETURN T_BREAK T_CONTINUE

// Keywords for functions and structure
%token T_FUNCTION T_MAIN T_START T_END

// Literals (values will be in yylval)
%token <str_val> T_IDENTIFIER
%token <int_val> T_INT_LITERAL
%token <float_val> T_FLOAT_LITERAL
%token <str_val> T_STRING_LITERAL
%token <int_val> T_BOOL_LITERAL
%token <str_val> T_CHAR_LITERAL

// Operators
%token T_ASSIGN T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_MODULO
%token T_PLUS_ASSIGN T_MINUS_ASSIGN T_STAR_ASSIGN T_SLASH_ASSIGN T_PERCENT_ASSIGN
%token T_EQ T_NEQ T_LT T_GT T_LTE T_GTE
%token T_AND T_OR T_NOT

// Punctuation
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_LBRACKET T_RBRACKET
%token T_COMMA T_SEMICOLON

// Custom Functions
%token T_MAHI_READ T_MAHI_WRITE T_MAHI_SORT T_MAHI_PUSH

// End of File
%token T_EOF

// Precedence-only token (not from lexer)
%token UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc T_ELSE

%right T_ASSIGN T_PLUS_ASSIGN T_MINUS_ASSIGN T_STAR_ASSIGN T_SLASH_ASSIGN T_PERCENT_ASSIGN
%right T_NOT UMINUS
%left T_OR
%left T_AND
%left T_EQ T_NEQ T_LT T_GT T_LTE T_GTE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_MODULO

/* === Type association for non-terminals === */
%type <type_val> type_specifier
%type <ast> program function_declarations function_declaration parameter_list opt_parameter_list parameter_decl statements statement block_statement declaration_statement expression_statement if_statement while_statement for_statement expression argument_list opt_argument_list

/* === Grammar Rules === */
%%

program:
    {
        init_symbol_table();
        if (linear_verbose)
            printf("Program Start: Global scope initialized.\n");
    }
    function_declarations T_START T_MAIN
    block_statement
    T_END
    {
        root = create_node(NODE_PROGRAM);
        root->middle = $2; // function declarations
        root->left = $5;   // main block
        if (linear_verbose) {
            printf("Parse successful: Program structure is valid.\n");
            print_ast(root, 0);
            print_all_scopes();
        }
    }
    ;

function_declarations:
    /* empty */ { $$ = NULL; }
    | function_declarations function_declaration
    {
        if ($1) {
            add_sibling($1, $2);
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    ;

function_declaration:
    T_FUNCTION type_specifier T_IDENTIFIER T_LPAREN opt_parameter_list T_RPAREN
    {
        enter_scope();
        insert_param_symbols($5);
    }
    block_statement
    {
        $$ = create_node(NODE_FUNC_DECL);
        $$->name = strdup($3);
        $$->int_val = $2; // return type
        $$->left = $5;    // params
        $$->right = $8;   // body
        exit_scope();
        free($3);
    }
    ;

parameter_decl:
    type_specifier T_IDENTIFIER
    {
        $$ = create_node(NODE_VAR_DECL);
        $$->name = strdup($2);
        $$->int_val = $1;
        free($2);
    }
    ;

parameter_list:
    parameter_decl { $$ = $1; }
    | parameter_list T_COMMA parameter_decl
    {
        add_sibling($1, $3);
        $$ = $1;
    }
    ;

opt_parameter_list:
    /* empty */ { $$ = NULL; }
    | parameter_list { $$ = $1; }
    ;

statements:
    /* empty */ { $$ = NULL; }
    | statement statements 
    {
        if ($1 != NULL) {
            $$ = $1;
            add_sibling($$, $2);
        } else {
            $$ = $2;
        }
    }
    ;

statement:
    declaration_statement { $$ = $1; }
    | expression_statement { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | for_statement { $$ = $1; }
    | block_statement { $$ = $1; }
    | T_BREAK T_SEMICOLON { $$ = create_node(NODE_BREAK); }
    | T_CONTINUE T_SEMICOLON { $$ = create_node(NODE_CONTINUE); }
    | T_RETURN expression T_SEMICOLON { $$ = create_node(NODE_RETURN); $$->left = $2; }
    | T_SEMICOLON { $$ = create_node(NODE_EMPTY); }
    ;

argument_list:
    expression { $$ = $1; }
    | argument_list T_COMMA expression { add_sibling($1, $3); $$ = $1; }
    ;

opt_argument_list:
    /* empty */ { $$ = NULL; }
    | argument_list { $$ = $1; }
    ;

block_statement:
    T_LBRACE 
    { 
        enter_scope(); 
    }
    statements 
    T_RBRACE
    {
        $$ = create_node(NODE_BLOCK);
        $$->left = $3;
        exit_scope();
    }
    ;

declaration_statement:
    type_specifier T_IDENTIFIER T_SEMICOLON
    {
        insert_symbol($2, $1, yylineno);
        $$ = create_node(NODE_VAR_DECL);
        $$->name = strdup($2);
        $$->int_val = $1;
        free($2); 
    }
    | type_specifier T_IDENTIFIER T_ASSIGN expression T_SEMICOLON
    {
        insert_symbol($2, $1, yylineno);
        $$ = create_node(NODE_VAR_DECL);
        $$->name = strdup($2);
        $$->int_val = $1;
        $$->left = $4;
        free($2);
    }
    ;

type_specifier:
    T_INT { $$ = TYPE_INT; }
    | T_FLOAT { $$ = TYPE_FLOAT; }
    | T_BOOL { $$ = TYPE_BOOL; }
    | T_CHAR { $$ = TYPE_CHAR; }
    | T_STRING { $$ = TYPE_STRING; }
    | T_VOID { $$ = TYPE_VOID; }
    | T_GRAPH { $$ = TYPE_GRAPH; }
    | T_TREE { $$ = TYPE_TREE; }
    | T_RANGE_TREE { $$ = TYPE_RANGE_TREE; }
    | T_DSU { $$ = TYPE_DSU; }
    | T_MATRIX { $$ = TYPE_MATRIX; }
    | T_ORDERED_SET { $$ = TYPE_ORDERED_SET; }
    | T_STACK { $$ = TYPE_STACK; }
    | T_QUEUE { $$ = TYPE_QUEUE; }
    ;

expression_statement:
    expression T_SEMICOLON { $$ = $1; }
    ;

if_statement:
    T_IF T_LPAREN expression T_RPAREN statement %prec LOWER_THAN_ELSE
    {
        $$ = create_node(NODE_IF);
        $$->left = $3;
        $$->right = $5;
    }
    | T_IF T_LPAREN expression T_RPAREN statement T_ELSE statement
    {
        $$ = create_node(NODE_IF);
        $$->left = $3;
        $$->middle = $5;
        $$->right = $7;
    }
    ;

while_statement:
    T_WHILE T_LPAREN expression T_RPAREN statement
    {
        $$ = create_node(NODE_WHILE);
        $$->left = $3;
        $$->right = $5;
    }
    ;

for_statement:
    T_FOR T_LPAREN declaration_statement expression T_SEMICOLON expression T_RPAREN statement
    {
        $$ = create_node(NODE_FOR);
        $$->left = $3;   // init
        $$->middle = $4; // cond
        $$->right = $6;  // inc
        $$->body = $8;   // body
    }
    | T_FOR T_LPAREN expression_statement expression T_SEMICOLON expression T_RPAREN statement
    {
        $$ = create_node(NODE_FOR);
        $$->left = $3;   // init
        $$->middle = $4; // cond
        $$->right = $6;  // inc
        $$->body = $8;   // body
    }
    ;

expression:
    T_IDENTIFIER T_ASSIGN expression
    {
        if (lookup_symbol($1) == NULL) {
            yyerror("Semantic Error: Assignment to undeclared identifier");
        }
        $$ = create_node(NODE_ASSIGN);
        $$->left = create_identifier_node($1);
        $$->right = $3;
        free($1);
    }
    | T_IDENTIFIER T_PLUS_ASSIGN expression
    {
        if (lookup_symbol($1) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        $$ = create_node(NODE_ASSIGN);
        $$->left = create_identifier_node($1);
        $$->right = create_binary_op_node("+", create_identifier_node(strdup($$->left->name)), $3);
        free($1);
    }
    | T_IDENTIFIER T_MINUS_ASSIGN expression
    {
        if (lookup_symbol($1) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        $$ = create_node(NODE_ASSIGN);
        $$->left = create_identifier_node($1);
        $$->right = create_binary_op_node("-", create_identifier_node(strdup($$->left->name)), $3);
        free($1);
    }
    | T_IDENTIFIER T_STAR_ASSIGN expression
    {
        if (lookup_symbol($1) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        $$ = create_node(NODE_ASSIGN);
        $$->left = create_identifier_node($1);
        $$->right = create_binary_op_node("*", create_identifier_node(strdup($$->left->name)), $3);
        free($1);
    }
    | T_IDENTIFIER T_SLASH_ASSIGN expression
    {
        if (lookup_symbol($1) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        $$ = create_node(NODE_ASSIGN);
        $$->left = create_identifier_node($1);
        $$->right = create_binary_op_node("/", create_identifier_node(strdup($$->left->name)), $3);
        free($1);
    }
    | T_IDENTIFIER T_PERCENT_ASSIGN expression
    {
        if (lookup_symbol($1) == NULL) yyerror("Semantic Error: Assignment to undeclared identifier");
        $$ = create_node(NODE_ASSIGN);
        $$->left = create_identifier_node($1);
        $$->right = create_binary_op_node("%", create_identifier_node(strdup($$->left->name)), $3);
        free($1);
    }
    | T_INT_LITERAL { $$ = create_int_literal_node($1); }
    | T_FLOAT_LITERAL { $$ = create_float_literal_node($1); }
    | T_STRING_LITERAL { $$ = create_string_literal_node($1); free($1); }
    | T_BOOL_LITERAL { $$ = create_node(NODE_LITERAL_BOOL); $$->int_val = $1; }
    | T_CHAR_LITERAL { $$ = create_char_literal_node($1); free($1); }
    | T_IDENTIFIER T_LPAREN opt_argument_list T_RPAREN {
        $$ = create_func_call_node($1, $3);
        free($1);
    }
    | T_IDENTIFIER {
        if (lookup_symbol($1) == NULL) {
            yyerror("Semantic Error: Use of undeclared identifier");
        }
        $$ = create_identifier_node($1);
        free($1);
    }
    | expression T_PLUS expression { $$ = create_binary_op_node("+", $1, $3); }
    | expression T_MINUS expression { $$ = create_binary_op_node("-", $1, $3); }
    | expression T_MULTIPLY expression { $$ = create_binary_op_node("*", $1, $3); }
    | expression T_DIVIDE expression { $$ = create_binary_op_node("/", $1, $3); }
    | expression T_MODULO expression { $$ = create_binary_op_node("%", $1, $3); }
    | expression T_EQ expression { $$ = create_binary_op_node("==", $1, $3); }
    | expression T_NEQ expression { $$ = create_binary_op_node("!=", $1, $3); }
    | expression T_LT expression { $$ = create_binary_op_node("<", $1, $3); }
    | expression T_GT expression { $$ = create_binary_op_node(">", $1, $3); }
    | expression T_LTE expression { $$ = create_binary_op_node("<=", $1, $3); }
    | expression T_GTE expression { $$ = create_binary_op_node(">=", $1, $3); }
    | expression T_AND expression { $$ = create_binary_op_node("&&", $1, $3); }
    | expression T_OR expression { $$ = create_binary_op_node("||", $1, $3); }
    | T_NOT expression { $$ = create_unary_op_node("!", $2); }
    | T_MINUS expression %prec UMINUS { $$ = create_unary_op_node("-", $2); }
    | T_LPAREN expression T_RPAREN { $$ = $2; }
    | T_MAHI_WRITE T_LPAREN expression T_RPAREN
    {
        $$ = create_func_call_node("MAHI_write", $3);
    }
    | T_MAHI_READ T_LPAREN T_IDENTIFIER T_RPAREN
    {
        if (lookup_symbol($3) == NULL) {
            yyerror("Semantic Error: Use of undeclared identifier");
        }
        $$ = create_func_call_node("MAHI_read", create_identifier_node($3));
        free($3);
    }
    | T_MAHI_SORT T_LPAREN expression T_RPAREN
    {
        $$ = create_func_call_node("MAHI_sort", $3);
    }
    | T_MAHI_PUSH T_LPAREN expression T_COMMA expression T_RPAREN
    {
        ASTNode *args = $3;
        add_sibling(args, $5);
        $$ = create_func_call_node("MAHI_push", args);
    }
    ;

%%

/* === C Code Section === */

int main(int argc, char **argv) {
    const char *path = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
            linear_verbose = 1;
        else if (argv[i][0] != '-')
            path = argv[i];
    }

    FILE *file = NULL;
    if (path) {
        file = fopen(path, "r");
        if (!file) {
            perror(path);
            return 1;
        }
        yyin = file;
    }

    int ok = yyparse() == 0;
    if (ok && root) {
        char tac_path[1024];
        int tac_ok = generate_three_address_code(root, path, tac_path, sizeof(tac_path));
        if (tac_ok == 0) {
            printf("3AC generated: %s\n", tac_path);
        } else {
            fprintf(stderr, "Warning: failed to generate 3AC (code=%d).\n", tac_ok);
        }

        char c_path[1024];
        int c_ok = generate_c_code(root, path, c_path, sizeof(c_path));
        if (c_ok == 0) {
            printf("C generated: %s\n", c_path);
        } else {
            fprintf(stderr, "Warning: failed to generate C code (code=%d).\n", c_ok);
        }

        char tok_path[1024];
        int tok_ok = generate_token_file(path, tok_path, sizeof(tok_path));
        if (tok_ok == 0) {
            printf("Tokens generated: %s\n", tok_path);
        } else {
            fprintf(stderr, "Warning: failed to generate token file (code=%d).\n", tok_ok);
        }

        interpret(root);
        free_ast(root);
        root = NULL;
    } else if (!ok) {
        fprintf(stderr, "Compilation failed.\n");
    }

    destroy_symbol_table();

    if (file)
        fclose(file);

    return ok ? 0 : 1;
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse Error at line %d: %s near '%s'\n", yylineno, s, yytext);
}

static void insert_param_symbols(ASTNode *params) {
    for (ASTNode *p = params; p; p = p->next) {
        if (p->name)
            insert_symbol(p->name, (DataType)p->int_val, yylineno);
    }
}

static const char *token_name(int tok) {
    switch (tok) {
        case T_INT: return "T_INT";
        case T_FLOAT: return "T_FLOAT";
        case T_BOOL: return "T_BOOL";
        case T_CHAR: return "T_CHAR";
        case T_STRING: return "T_STRING";
        case T_VOID: return "T_VOID";
        case T_GRAPH: return "T_GRAPH";
        case T_TREE: return "T_TREE";
        case T_RANGE_TREE: return "T_RANGE_TREE";
        case T_DSU: return "T_DSU";
        case T_MATRIX: return "T_MATRIX";
        case T_ORDERED_SET: return "T_ORDERED_SET";
        case T_STACK: return "T_STACK";
        case T_QUEUE: return "T_QUEUE";
        case T_IF: return "T_IF";
        case T_ELSE: return "T_ELSE";
        case T_FOR: return "T_FOR";
        case T_WHILE: return "T_WHILE";
        case T_RETURN: return "T_RETURN";
        case T_BREAK: return "T_BREAK";
        case T_CONTINUE: return "T_CONTINUE";
        case T_FUNCTION: return "T_FUNCTION";
        case T_MAIN: return "T_MAIN";
        case T_START: return "T_START";
        case T_END: return "T_END";
        case T_IDENTIFIER: return "T_IDENTIFIER";
        case T_INT_LITERAL: return "T_INT_LITERAL";
        case T_FLOAT_LITERAL: return "T_FLOAT_LITERAL";
        case T_STRING_LITERAL: return "T_STRING_LITERAL";
        case T_BOOL_LITERAL: return "T_BOOL_LITERAL";
        case T_CHAR_LITERAL: return "T_CHAR_LITERAL";
        case T_ASSIGN: return "T_ASSIGN";
        case T_PLUS: return "T_PLUS";
        case T_MINUS: return "T_MINUS";
        case T_MULTIPLY: return "T_MULTIPLY";
        case T_DIVIDE: return "T_DIVIDE";
        case T_MODULO: return "T_MODULO";
        case T_PLUS_ASSIGN: return "T_PLUS_ASSIGN";
        case T_MINUS_ASSIGN: return "T_MINUS_ASSIGN";
        case T_STAR_ASSIGN: return "T_STAR_ASSIGN";
        case T_SLASH_ASSIGN: return "T_SLASH_ASSIGN";
        case T_PERCENT_ASSIGN: return "T_PERCENT_ASSIGN";
        case T_EQ: return "T_EQ";
        case T_NEQ: return "T_NEQ";
        case T_LT: return "T_LT";
        case T_GT: return "T_GT";
        case T_LTE: return "T_LTE";
        case T_GTE: return "T_GTE";
        case T_AND: return "T_AND";
        case T_OR: return "T_OR";
        case T_NOT: return "T_NOT";
        case T_LPAREN: return "T_LPAREN";
        case T_RPAREN: return "T_RPAREN";
        case T_LBRACE: return "T_LBRACE";
        case T_RBRACE: return "T_RBRACE";
        case T_LBRACKET: return "T_LBRACKET";
        case T_RBRACKET: return "T_RBRACKET";
        case T_COMMA: return "T_COMMA";
        case T_SEMICOLON: return "T_SEMICOLON";
        case T_MAHI_READ: return "T_MAHI_READ";
        case T_MAHI_WRITE: return "T_MAHI_WRITE";
        case T_MAHI_SORT: return "T_MAHI_SORT";
        case T_MAHI_PUSH: return "T_MAHI_PUSH";
        default: return "UNKNOWN_TOKEN";
    }
}

static void free_token_payload_if_needed(int tok) {
    if (tok == T_IDENTIFIER || tok == T_STRING_LITERAL || tok == T_CHAR_LITERAL) {
        if (yylval.str_val) {
            free(yylval.str_val);
            yylval.str_val = NULL;
        }
    }
}

static int generate_token_file(const char *source_path, char *out_path, size_t out_path_size) {
    if (!source_path || !*source_path) return -1;

    char path_buf[1024];
    snprintf(path_buf, sizeof(path_buf), "%s", source_path);
    char *slash1 = strrchr(path_buf, '/');
    char *slash2 = strrchr(path_buf, '\\');
    char *slash = slash1 > slash2 ? slash1 : slash2;
    char *dot = strrchr(path_buf, '.');
    if (dot && (!slash || dot > slash)) {
        *dot = '\0';
    }

    if (strlen(path_buf) + strlen(".tokens.txt") + 1 > sizeof(path_buf)) return -2;
    strcat(path_buf, ".tokens.txt");

    FILE *in = fopen(source_path, "r");
    if (!in) return -3;
    FILE *out = fopen(path_buf, "w");
    if (!out) {
        fclose(in);
        return -4;
    }

    FILE *old_yyin = yyin;
    int old_lineno = yylineno;

    yyin = in;
    yylineno = 1;

    fprintf(out, "# Tokens for %s\n", source_path);
    fprintf(out, "# Format: line\tTOKEN\tLEXEME\n\n");

    int tok;
    while ((tok = yylex()) != 0) {
        fprintf(out, "%d\t%s\t%s\n", yylineno, token_name(tok), yytext ? yytext : "");
        free_token_payload_if_needed(tok);
    }

    yyin = old_yyin;
    yylineno = old_lineno;

    fclose(out);
    fclose(in);

    if (out_path && out_path_size > 0) {
        snprintf(out_path, out_path_size, "%s", path_buf);
    }

    return 0;
}
