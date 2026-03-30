#ifndef TAC_GEN_H
#define TAC_GEN_H

#include <stddef.h>
#include "ast.h"

/*
 * Generates three-address-code text for a parsed program AST.
 * - root: AST root (NODE_PROGRAM)
 * - source_path: input .linear path (can be NULL)
 * - out_path: optional output buffer to receive actual emitted path
 * - out_path_size: size of out_path buffer
 * Returns 0 on success, non-zero on failure.
 */
int generate_three_address_code(ASTNode *root, const char *source_path,
                                char *out_path, size_t out_path_size);

#endif
