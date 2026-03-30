/*
 * Symbol Table Implementation
 * Author: Khadimul Islam Mahi (2107076)
 * 
 * Implements the functions for the symbol table as defined in symbol_table.h.
 * This implementation uses a stack of hash tables to manage scopes.
 */

#include "symbol_table.h"

int linear_verbose = 0;

// Global variables for scope management
static Scope* current_scope = NULL;
static int scope_level = 0;

/* === Scope Management Functions === */

/**
 * @brief Initializes the global symbol table by creating the global scope.
 */
void init_symbol_table() {
    scope_level = 0;
    current_scope = (Scope*)malloc(sizeof(Scope));
    if (!current_scope) {
        fprintf(stderr, "Fatal Error: Could not allocate memory for global scope.\n");
        exit(EXIT_FAILURE);
    }
    current_scope->level = scope_level;
    current_scope->head = NULL;
    current_scope->parent = NULL;
    if (linear_verbose)
        printf("Initialized global scope at level %d\n", scope_level);
}

/**
 * @brief Enters a new, nested scope.
 */
void enter_scope() {
    scope_level++;
    Scope* new_scope = (Scope*)malloc(sizeof(Scope));
    if (!new_scope) {
        fprintf(stderr, "Fatal Error: Could not allocate memory for new scope.\n");
        exit(EXIT_FAILURE);
    }
    new_scope->level = scope_level;
    new_scope->head = NULL;
    new_scope->parent = current_scope;
    current_scope = new_scope;
    if (linear_verbose)
        printf("Entered new scope at level %d\n", scope_level);
}

/**
 * @brief Exits the current scope and returns to the parent scope.
 */
void exit_scope() {
    if (current_scope->parent == NULL) {
        if (linear_verbose)
            printf("Warning: Attempted to exit global scope. No action taken.\n");
        return;
    }

    if (linear_verbose)
        printf("Exiting scope at level %d\n", scope_level);
    
    Scope* parent_scope = current_scope->parent;
    
    // Free all symbols in the current scope
    Symbol* current_symbol = current_scope->head;
    while (current_symbol != NULL) {
        Symbol* temp = current_symbol;
        current_symbol = current_symbol->next;
        free(temp);
    }
    
    // Free the current scope itself and move up
    free(current_scope);
    current_scope = parent_scope;
    scope_level--;
}

/* === Symbol Manipulation Functions === */

/**
 * @brief Inserts a new symbol into the current scope.
 * @param name The name of the identifier.
 * @param type The data type of the identifier.
 * @param line The line number where it was declared.
 * @return A pointer to the newly created symbol, or NULL if it already exists in the current scope.
 */
Symbol* insert_symbol(const char* name, DataType type, int line) {
    if (lookup_in_current_scope(name) != NULL) {
        fprintf(stderr, "Semantic Error at line %d: Redeclaration of identifier '%s' in the same scope.\n", line, name);
        return NULL;
    }

    Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
    if (!new_symbol) {
        fprintf(stderr, "Fatal Error: Could not allocate memory for new symbol.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(new_symbol->name, name, MAX_ID_LENGTH - 1);
    new_symbol->name[MAX_ID_LENGTH - 1] = '\0';
    new_symbol->type = type;
    new_symbol->scope = current_scope->level;
    new_symbol->line_declared = line;
    new_symbol->next = current_scope->head; // Prepend to the list
    current_scope->head = new_symbol;

    if (linear_verbose)
        printf("Inserted symbol '%s' with type %s into scope %d.\n", name, data_type_to_string(type), current_scope->level);
    return new_symbol;
}

/**
 * @brief Looks for a symbol in the current scope and all parent scopes.
 * @param name The name of the symbol to find.
 * @return A pointer to the symbol if found, otherwise NULL.
 */
Symbol* lookup_symbol(const char* name) {
    Scope* temp_scope = current_scope;
    while (temp_scope != NULL) {
        Symbol* current_symbol = temp_scope->head;
        while (current_symbol != NULL) {
            if (strcmp(current_symbol->name, name) == 0) {
                return current_symbol;
            }
            current_symbol = current_symbol->next;
        }
        temp_scope = temp_scope->parent;
    }
    return NULL;
}

/**
 * @brief Looks for a symbol only in the current scope.
 * @param name The name of the symbol to find.
 * @return A pointer to the symbol if found, otherwise NULL.
 */
Symbol* lookup_in_current_scope(const char* name) {
    Symbol* current_symbol = current_scope->head;
    while (current_symbol != NULL) {
        if (strcmp(current_symbol->name, name) == 0) {
            return current_symbol;
        }
        current_symbol = current_symbol->next;
    }
    return NULL; // Not found in the current scope
}


/* === Utility Functions === */

/**
 * @brief Converts a DataType enum to its string representation.
 * @param type The DataType to convert.
 * @return A constant string representing the type.
 */
const char* data_type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "INT";
        case TYPE_FLOAT: return "FLOAT";
        case TYPE_BOOL: return "BOOL";
        case TYPE_CHAR: return "CHAR";
        case TYPE_STRING: return "STRING";
        case TYPE_VOID: return "VOID";
        case TYPE_GRAPH: return "GRAPH";
        case TYPE_TREE: return "TREE";
        case TYPE_RANGE_TREE: return "RANGE_TREE";
        case TYPE_DSU: return "DSU";
        case TYPE_MATRIX: return "MATRIX";
        case TYPE_ORDERED_SET: return "ORDERED_SET";
        case TYPE_STACK: return "STACK";
        case TYPE_QUEUE: return "QUEUE";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Prints all symbols in the current scope.
 */
void print_current_scope() {
    printf("\n--- Symbol Table (Scope Level: %d) ---\n", current_scope->level);
    printf("%-20s | %-15s | %-10s | %-10s\n", "Name", "Type", "Scope", "Line");
    printf("----------------------------------------------------------------\n");

    Symbol* current_symbol = current_scope->head;
    if (current_symbol == NULL) {
        printf("Scope is empty.\n");
    } else {
        while (current_symbol != NULL) {
            printf("%-20s | %-15s | %-10d | %-10d\n",
                   current_symbol->name,
                   data_type_to_string(current_symbol->type),
                   current_symbol->scope,
                   current_symbol->line_declared);
            current_symbol = current_symbol->next;
        }
    }
    printf("----------------------------------------------------------------\n\n");
}

/**
 * @brief Prints all symbols in all scopes, from current to global.
 */
void print_all_scopes() {
    printf("\n=== All Accessible Symbols ===\n");
    Scope* temp_scope = current_scope;
    while (temp_scope != NULL) {
        // This is not ideal, as it re-uses print_current_scope which prints the *current* scope's header
        // A better implementation would pass the scope to print. For now, this is a simple visualization.
        printf("\n--- Symbols in Scope Level: %d ---\n", temp_scope->level);
        printf("%-20s | %-15s | %-10s | %-10s\n", "Name", "Type", "Scope", "Line");
        printf("----------------------------------------------------------------\n");
        Symbol* current_symbol = temp_scope->head;
        if (current_symbol == NULL) {
            printf("Scope is empty.\n");
        } else {
            while (current_symbol != NULL) {
                printf("%-20s | %-15s | %-10d | %-10d\n",
                       current_symbol->name,
                       data_type_to_string(current_symbol->type),
                       current_symbol->scope,
                       current_symbol->line_declared);
                current_symbol = current_symbol->next;
            }
        }
        printf("----------------------------------------------------------------\n\n");
        temp_scope = temp_scope->parent;
    }
}

void destroy_symbol_table(void) {
    Scope *sc = current_scope;
    while (sc != NULL) {
        Symbol *sym = sc->head;
        while (sym != NULL) {
            Symbol *nx = sym->next;
            free(sym);
            sym = nx;
        }
        Scope *parent = sc->parent;
        free(sc);
        sc = parent;
    }
    current_scope = NULL;
    scope_level = 0;
}
