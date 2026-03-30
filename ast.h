/*
 * Abstract Syntax Tree Header
 * Author: Khadimul Islam Mahi (2107076)
 *
 * Defines the structures and function prototypes for the AST
 * used in the Linear language compiler.
 */

#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types of AST Nodes
typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_VAR_DECL,
    NODE_ASSIGN,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_FUNC_CALL,
    NODE_RETURN,
    NODE_BINARY_OP,
    NODE_LITERAL_INT,
    NODE_LITERAL_FLOAT,
    NODE_LITERAL_STRING,
    NODE_LITERAL_BOOL,
    NODE_LITERAL_CHAR,
    NODE_IDENTIFIER,
    NODE_UNARY_OP,
    NODE_BREAK,
    NODE_CONTINUE,
    NODE_EMPTY
} NodeType;

// Represents an AST Node
typedef struct ASTNode {
    NodeType type;
    char* name; // E.g., for identifiers, strings, op symbols
    int int_val;
    float float_val;
    
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* middle; // Used for for-loops or if-else
    struct ASTNode* body;   // Used for for-loops body

    struct ASTNode* next;   // For sibling nodes in a block or list
    struct ASTNode* call_args; /* First argument for NODE_FUNC_CALL (chain via next) */
} ASTNode;

/* === Function Prototypes === */

ASTNode* create_node(NodeType type);
ASTNode* create_identifier_node(const char* name);
ASTNode* create_int_literal_node(int val);
ASTNode* create_float_literal_node(float val);
ASTNode* create_string_literal_node(const char* val);
ASTNode* create_binary_op_node(const char* op, ASTNode* left, ASTNode* right);
ASTNode* create_unary_op_node(const char* op, ASTNode* operand);
ASTNode* create_char_literal_node(const char* raw);
ASTNode* create_func_call_node(const char* name, ASTNode* call_args);

void add_sibling(ASTNode* list, ASTNode* sibling);
void print_ast(ASTNode* node, int level);
void free_ast(ASTNode* node);

#endif // AST_H
