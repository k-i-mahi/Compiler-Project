/*
 * Symbol Table Header
 * Author: Khadimul Islam Mahi (2107076)
 * 
 * Defines the structures and function prototypes for the symbol table
 * used in the Linear language compiler.
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum length for an identifier
#define MAX_ID_LENGTH 64

// Data types supported by the language
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_VOID,
    TYPE_GRAPH,
    TYPE_TREE,
    TYPE_RANGE_TREE,
    TYPE_DSU,
    TYPE_MATRIX,
    TYPE_ORDERED_SET,
    TYPE_STACK,
    TYPE_QUEUE,
    TYPE_UNKNOWN
} DataType;

// Structure for a symbol table entry
typedef struct Symbol {
    char name[MAX_ID_LENGTH];
    DataType type;
    int scope;
    int line_declared;
    struct Symbol *next; // For linked list implementation
} Symbol;

// Structure for a symbol table scope
typedef struct Scope {
    int level;
    Symbol *head;
    struct Scope *parent;
} Scope;

/* === Function Prototypes === */

// Scope management
void init_symbol_table();
void enter_scope();
void exit_scope();

// Symbol manipulation
Symbol* insert_symbol(const char* name, DataType type, int line);
Symbol* lookup_symbol(const char* name);
Symbol* lookup_in_current_scope(const char* name);

// Utility
const char* data_type_to_string(DataType type);
void print_current_scope();
void print_all_scopes();

extern int linear_verbose;
void destroy_symbol_table(void);

#endif // SYMBOL_TABLE_H

