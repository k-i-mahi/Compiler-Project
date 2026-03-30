/*
 * Abstract Syntax Tree Implementation
 * Author: Khadimul Islam Mahi (2107076)
 */

#include "ast.h"

ASTNode* create_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Fatal Error: Memory allocation failed for ASTNode.\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->name = NULL;
    node->int_val = 0;
    node->float_val = 0.0;
    node->left = NULL;
    node->right = NULL;
    node->middle = NULL;
    node->body = NULL;
    node->next = NULL;
    node->call_args = NULL;
    return node;
}

ASTNode* create_identifier_node(const char* name) {
    ASTNode* node = create_node(NODE_IDENTIFIER);
    node->name = strdup(name);
    return node;
}

ASTNode* create_int_literal_node(int val) {
    ASTNode* node = create_node(NODE_LITERAL_INT);
    node->int_val = val;
    return node;
}

ASTNode* create_float_literal_node(float val) {
    ASTNode* node = create_node(NODE_LITERAL_FLOAT);
    node->float_val = val;
    return node;
}

ASTNode* create_string_literal_node(const char* val) {
    ASTNode* node = create_node(NODE_LITERAL_STRING);
    node->name = strdup(val);
    return node;
}

ASTNode* create_binary_op_node(const char* op, ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(NODE_BINARY_OP);
    node->name = strdup(op);
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_unary_op_node(const char* op, ASTNode* operand) {
    ASTNode* node = create_node(NODE_UNARY_OP);
    node->name = strdup(op);
    node->left = operand;
    node->right = NULL;
    return node;
}

ASTNode* create_func_call_node(const char* name, ASTNode* call_args) {
    ASTNode* node = create_node(NODE_FUNC_CALL);
    node->name = strdup(name);
    node->call_args = call_args;
    return node;
}

ASTNode* create_char_literal_node(const char* raw) {
    ASTNode* node = create_node(NODE_LITERAL_CHAR);
    node->int_val = 0;
    if (raw && raw[0] == '\'' && raw[1] != '\0') {
        if (raw[1] == '\\' && raw[2] != '\0') {
            switch (raw[2]) {
                case 'n': node->int_val = '\n'; break;
                case 't': node->int_val = '\t'; break;
                case 'r': node->int_val = '\r'; break;
                case '\\': node->int_val = '\\'; break;
                case '\'': node->int_val = '\''; break;
                default: node->int_val = (unsigned char)raw[2]; break;
            }
        } else {
            node->int_val = (unsigned char)raw[1];
        }
    }
    return node;
}

void add_sibling(ASTNode* list, ASTNode* sibling) {
    if (!list) return;
    ASTNode* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = sibling;
}

void print_ast(ASTNode* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; ++i) printf("  ");

    switch (node->type) {
        case NODE_PROGRAM: printf("Program\n"); break;
        case NODE_BLOCK: printf("Block\n"); break;
        case NODE_VAR_DECL: printf("VarDecl: %s\n", node->name ? node->name : ""); break;
        case NODE_ASSIGN: printf("Assign\n"); break;
        case NODE_IF: printf("If\n"); break;
        case NODE_WHILE: printf("While\n"); break;
        case NODE_FOR: printf("For\n"); break;
        case NODE_FUNC_CALL: printf("FuncCall: %s\n", node->name ? node->name : ""); break;
        case NODE_RETURN: printf("Return\n"); break;
        case NODE_BINARY_OP: printf("BinaryOp: %s\n", node->name ? node->name : ""); break;
        case NODE_LITERAL_INT: printf("IntLiteral: %d\n", node->int_val); break;
        case NODE_LITERAL_FLOAT: printf("FloatLiteral: %f\n", node->float_val); break;
        case NODE_LITERAL_STRING: printf("StringLiteral: %s\n", node->name ? node->name : ""); break;
        case NODE_LITERAL_BOOL: printf("BoolLiteral: %d\n", node->int_val); break;
        case NODE_LITERAL_CHAR: printf("CharLiteral: %d\n", node->int_val); break;
        case NODE_UNARY_OP: printf("UnaryOp: %s\n", node->name ? node->name : ""); break;
        case NODE_IDENTIFIER: printf("Identifier: %s\n", node->name ? node->name : ""); break;
        case NODE_BREAK: printf("Break\n"); break;
        case NODE_CONTINUE: printf("Continue\n"); break;
        case NODE_EMPTY: printf("Empty\n"); break;
        default: printf("UnknownNode\n"); break;
    }

    if (node->type == NODE_FUNC_CALL && node->call_args) {
        print_ast(node->call_args, level + 1);
    } else {
        if (node->left) print_ast(node->left, level + 1);
        if (node->middle) print_ast(node->middle, level + 1);
        if (node->right) print_ast(node->right, level + 1);
    }
    if (node->next) print_ast(node->next, level);
}

void free_ast(ASTNode* node) {
    if (!node) return;
    if (node->name) free(node->name);
    free_ast(node->call_args);
    free_ast(node->left);
    free_ast(node->middle);
    free_ast(node->right);
    free_ast(node->body);
    free_ast(node->next);
    free(node);
}
