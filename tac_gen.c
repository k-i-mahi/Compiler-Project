#include "tac_gen.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    FILE *out;
    int temp_id;
    int label_id;
    int loop_top;
    char break_labels[64][32];
    char continue_labels[64][32];
} TacGen;

static void emitf(TacGen *g, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(g->out, fmt, ap);
    va_end(ap);
    fputc('\n', g->out);
}

static char *dup_printf(const char *prefix, int id) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%s%d", prefix, id);
    return strdup(buf);
}

static char *new_temp(TacGen *g) {
    return dup_printf("t", ++g->temp_id);
}

static char *new_label(TacGen *g, const char *prefix) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%s_%d", prefix, ++g->label_id);
    return strdup(buf);
}

static int count_args(ASTNode *args) {
    int c = 0;
    for (ASTNode *a = args; a; a = a->next) c++;
    return c;
}

static char *emit_expr(TacGen *g, ASTNode *n);
static void emit_stmt(TacGen *g, ASTNode *n);

static char *emit_call(TacGen *g, ASTNode *call, int need_result) {
    ASTNode *args = call->call_args ? call->call_args : call->left;
    int argc = count_args(args);

    for (ASTNode *a = args; a; a = a->next) {
        char *op = emit_expr(g, a);
        emitf(g, "    param %s", op);
        free(op);
    }

    if (need_result) {
        char *t = new_temp(g);
        emitf(g, "    %s = call %s, %d", t, call->name ? call->name : "<anon>", argc);
        return t;
    }

    emitf(g, "    call %s, %d", call->name ? call->name : "<anon>", argc);
    return NULL;
}

static char *emit_expr(TacGen *g, ASTNode *n) {
    if (!n) return strdup("0");

    switch (n->type) {
        case NODE_LITERAL_INT: {
            char buf[64];
            snprintf(buf, sizeof(buf), "%d", n->int_val);
            return strdup(buf);
        }
        case NODE_LITERAL_FLOAT: {
            char buf[64];
            snprintf(buf, sizeof(buf), "%g", n->float_val);
            return strdup(buf);
        }
        case NODE_LITERAL_BOOL:
            return strdup(n->int_val ? "true" : "false");
        case NODE_LITERAL_CHAR: {
            char buf[64];
            snprintf(buf, sizeof(buf), "'%c'", (char)n->int_val);
            return strdup(buf);
        }
        case NODE_LITERAL_STRING: {
            const char *s = n->name ? n->name : "\"\"";
            return strdup(s);
        }
        case NODE_IDENTIFIER:
            return strdup(n->name ? n->name : "<id>");
        case NODE_FUNC_CALL:
            return emit_call(g, n, 1);
        case NODE_ASSIGN: {
            char *rhs = emit_expr(g, n->right);
            const char *lhs = (n->left && n->left->type == NODE_IDENTIFIER && n->left->name)
                                  ? n->left->name
                                  : "<lhs>";
            emitf(g, "    %s = %s", lhs, rhs);
            free(rhs);
            return strdup(lhs);
        }
        case NODE_UNARY_OP: {
            char *a = emit_expr(g, n->left);
            char *t = new_temp(g);
            emitf(g, "    %s = %s %s", t, n->name ? n->name : "?", a);
            free(a);
            return t;
        }
        case NODE_BINARY_OP: {
            char *l = emit_expr(g, n->left);
            char *r = emit_expr(g, n->right);
            char *t = new_temp(g);
            emitf(g, "    %s = %s %s %s", t, l, n->name ? n->name : "?", r);
            free(l);
            free(r);
            return t;
        }
        default:
            return strdup("0");
    }
}

static void emit_stmt_or_block(TacGen *g, ASTNode *n) {
    if (!n) return;
    if (n->type == NODE_BLOCK) {
        for (ASTNode *s = n->left; s; s = s->next) emit_stmt(g, s);
    } else {
        emit_stmt(g, n);
    }
}

static void emit_stmt(TacGen *g, ASTNode *n) {
    if (!n) return;

    switch (n->type) {
        case NODE_EMPTY:
            break;
        case NODE_VAR_DECL: {
            if (n->left) {
                char *v = emit_expr(g, n->left);
                emitf(g, "    %s = %s", n->name ? n->name : "<var>", v);
                free(v);
            } else {
                emitf(g, "    %s = 0", n->name ? n->name : "<var>");
            }
            break;
        }
        case NODE_ASSIGN:
        case NODE_BINARY_OP:
        case NODE_UNARY_OP:
        case NODE_IDENTIFIER:
        case NODE_LITERAL_INT:
        case NODE_LITERAL_FLOAT:
        case NODE_LITERAL_BOOL:
        case NODE_LITERAL_STRING:
        case NODE_LITERAL_CHAR: {
            char *v = emit_expr(g, n);
            free(v);
            break;
        }
        case NODE_FUNC_CALL:
            emit_call(g, n, 0);
            break;
        case NODE_RETURN: {
            char *v = emit_expr(g, n->left);
            emitf(g, "    return %s", v);
            free(v);
            break;
        }
        case NODE_BREAK:
            if (g->loop_top > 0)
                emitf(g, "    goto %s", g->break_labels[g->loop_top - 1]);
            else
                emitf(g, "    # break (outside loop)");
            break;
        case NODE_CONTINUE:
            if (g->loop_top > 0)
                emitf(g, "    goto %s", g->continue_labels[g->loop_top - 1]);
            else
                emitf(g, "    # continue (outside loop)");
            break;
        case NODE_IF: {
            ASTNode *then_node = n->middle ? n->middle : n->right;
            ASTNode *else_node = n->middle ? n->right : NULL;

            char *cond = emit_expr(g, n->left);
            char *l_else = new_label(g, "L_else");
            char *l_end = new_label(g, "L_if_end");

            emitf(g, "    ifFalse %s goto %s", cond, l_else);
            emit_stmt_or_block(g, then_node);
            emitf(g, "    goto %s", l_end);
            emitf(g, "%s:", l_else);
            if (else_node) emit_stmt_or_block(g, else_node);
            emitf(g, "%s:", l_end);

            free(cond);
            free(l_else);
            free(l_end);
            break;
        }
        case NODE_WHILE: {
            char *l_cond = new_label(g, "L_while_cond");
            char *l_end = new_label(g, "L_while_end");

            strncpy(g->break_labels[g->loop_top], l_end, sizeof(g->break_labels[0]) - 1);
            g->break_labels[g->loop_top][sizeof(g->break_labels[0]) - 1] = '\0';
            strncpy(g->continue_labels[g->loop_top], l_cond, sizeof(g->continue_labels[0]) - 1);
            g->continue_labels[g->loop_top][sizeof(g->continue_labels[0]) - 1] = '\0';
            g->loop_top++;

            emitf(g, "%s:", l_cond);
            char *cond = emit_expr(g, n->left);
            emitf(g, "    ifFalse %s goto %s", cond, l_end);
            free(cond);
            emit_stmt_or_block(g, n->right);
            emitf(g, "    goto %s", l_cond);
            emitf(g, "%s:", l_end);

            g->loop_top--;
            free(l_cond);
            free(l_end);
            break;
        }
        case NODE_FOR: {
            char *l_cond = new_label(g, "L_for_cond");
            char *l_inc = new_label(g, "L_for_inc");
            char *l_end = new_label(g, "L_for_end");

            if (n->left) emit_stmt(g, n->left);

            strncpy(g->break_labels[g->loop_top], l_end, sizeof(g->break_labels[0]) - 1);
            g->break_labels[g->loop_top][sizeof(g->break_labels[0]) - 1] = '\0';
            strncpy(g->continue_labels[g->loop_top], l_inc, sizeof(g->continue_labels[0]) - 1);
            g->continue_labels[g->loop_top][sizeof(g->continue_labels[0]) - 1] = '\0';
            g->loop_top++;

            emitf(g, "%s:", l_cond);
            if (n->middle) {
                char *cond = emit_expr(g, n->middle);
                emitf(g, "    ifFalse %s goto %s", cond, l_end);
                free(cond);
            }

            emit_stmt_or_block(g, n->body);
            emitf(g, "%s:", l_inc);
            if (n->right) {
                char *inc = emit_expr(g, n->right);
                free(inc);
            }
            emitf(g, "    goto %s", l_cond);
            emitf(g, "%s:", l_end);

            g->loop_top--;
            free(l_cond);
            free(l_inc);
            free(l_end);
            break;
        }
        case NODE_BLOCK:
            for (ASTNode *s = n->left; s; s = s->next) emit_stmt(g, s);
            break;
        default:
            emitf(g, "    # unhandled node type %d", (int)n->type);
            break;
    }
}

static int make_output_path(const char *src, char *dst, size_t dstsz) {
    if (!dst || dstsz == 0) return -1;
    if (!src || !*src) {
        snprintf(dst, dstsz, "output.3ac.txt");
        return 0;
    }

    snprintf(dst, dstsz, "%s", src);

    char *slash1 = strrchr(dst, '/');
    char *slash2 = strrchr(dst, '\\');
    char *slash = slash1 > slash2 ? slash1 : slash2;
    char *dot = strrchr(dst, '.');

    if (dot && (!slash || dot > slash)) {
        *dot = '\0';
    }

    size_t len = strlen(dst);
    if (len + strlen(".3ac.txt") + 1 > dstsz) return -1;
    strcat(dst, ".3ac.txt");
    return 0;
}

static void emit_function(TacGen *g, ASTNode *fn) {
    emitf(g, "function %s:", fn->name ? fn->name : "<anon>");

    int idx = 0;
    for (ASTNode *p = fn->left; p; p = p->next) {
        emitf(g, "    # param %d: %s", idx++, p->name ? p->name : "<p>");
    }

    emit_stmt_or_block(g, fn->right);
    emitf(g, "");
}

int generate_three_address_code(ASTNode *root, const char *source_path,
                                char *out_path, size_t out_path_size) {
    if (!root || root->type != NODE_PROGRAM) return -1;

    char local_path[1024];
    if (make_output_path(source_path, local_path, sizeof(local_path)) != 0) {
        return -2;
    }

    FILE *fp = fopen(local_path, "w");
    if (!fp) return -3;

    TacGen g;
    memset(&g, 0, sizeof(g));
    g.out = fp;

    emitf(&g, "# Auto-generated Three Address Code");
    emitf(&g, "# Source: %s", source_path ? source_path : "<stdin>");
    emitf(&g, "");

    for (ASTNode *fn = root->middle; fn; fn = fn->next) {
        if (fn->type == NODE_FUNC_DECL) {
            emit_function(&g, fn);
        }
    }

    emitf(&g, "main:");
    emit_stmt_or_block(&g, root->left);
    emitf(&g, "    halt");

    fclose(fp);

    if (out_path && out_path_size > 0) {
        snprintf(out_path, out_path_size, "%s", local_path);
    }

    return 0;
}
