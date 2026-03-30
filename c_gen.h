#ifndef C_GEN_H
#define C_GEN_H

#include <stddef.h>
#include "ast.h"

/*
 * Generates C source from program AST.
 * Output file path pattern: <input_without_ext>.generated.c
 * Returns 0 on success, non-zero on error.
 */
int generate_c_code(ASTNode *root, const char *source_path,
                    char *out_path, size_t out_path_size);

#endif
