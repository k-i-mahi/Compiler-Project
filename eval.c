/*
 * Tree-walking interpreter for Linear language
 */

#include "eval.h"
#include "symbol_table.h"
#include "ds_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

typedef enum {
    VAL_INT,
    VAL_FLOAT,
    VAL_BOOL,
    VAL_STRING,
    VAL_GRAPH,
    VAL_TREE,
    VAL_RANGE_TREE,
    VAL_DSU,
    VAL_MATRIX,
    VAL_ORDERED_SET,
    VAL_STACK,
    VAL_QUEUE
} ValKind;

typedef struct Value {
    ValKind kind;
    int i;
    double f;
    char *s;
    void *obj;
} Value;

typedef struct VarNode {
    char name[MAX_ID_LENGTH];
    Value val;
    struct VarNode *next;
} VarNode;

typedef struct Env {
    VarNode *head;
    struct Env *parent;
} Env;

static Env *env_current = NULL;
static ASTNode *g_function_decls = NULL;

typedef enum {
    EV_OK,
    EV_BREAK,
    EV_CONTINUE,
    EV_RETURN
} EvalResult;

static int g_has_return = 0;
static Value g_return_value;

static void value_clear(Value *v) {
    switch (v->kind) {
        case VAL_STRING:
            if (v->s) free(v->s);
            v->s = NULL;
            break;
        case VAL_GRAPH:
            lin_graph_free((LinGraph *)v->obj);
            v->obj = NULL;
            break;
        case VAL_TREE:
            lin_tree_free((LinTree *)v->obj);
            v->obj = NULL;
            break;
        case VAL_DSU:
            lin_dsu_free((LinDSU *)v->obj);
            v->obj = NULL;
            break;
        case VAL_MATRIX:
            lin_matrix_free((LinMatrix *)v->obj);
            v->obj = NULL;
            break;
        case VAL_ORDERED_SET:
            lin_oset_free((LinOSet *)v->obj);
            v->obj = NULL;
            break;
        case VAL_RANGE_TREE:
            lin_segtree_free((LinSegTree *)v->obj);
            v->obj = NULL;
            break;
        case VAL_STACK:
            lin_stack_free((LinStack *)v->obj);
            v->obj = NULL;
            break;
        case VAL_QUEUE:
            lin_queue_free((LinQueue *)v->obj);
            v->obj = NULL;
            break;
        default:
            break;
    }
}

static Value value_dup(const Value *v) {
    Value o = *v;
    o.s = NULL;
    o.obj = NULL;
    if (v->kind == VAL_STRING && v->s)
        o.s = strdup(v->s);
    else if (v->kind == VAL_GRAPH && v->obj)
        o.obj = lin_graph_grab((LinGraph *)v->obj);
    else if (v->kind == VAL_TREE && v->obj)
        o.obj = lin_tree_grab((LinTree *)v->obj);
    else if (v->kind == VAL_DSU && v->obj)
        o.obj = lin_dsu_grab((LinDSU *)v->obj);
    else if (v->kind == VAL_MATRIX && v->obj)
        o.obj = lin_matrix_grab((LinMatrix *)v->obj);
    else if (v->kind == VAL_ORDERED_SET && v->obj)
        o.obj = lin_oset_grab((LinOSet *)v->obj);
    else if (v->kind == VAL_RANGE_TREE && v->obj)
        o.obj = lin_segtree_grab((LinSegTree *)v->obj);
    else if (v->kind == VAL_STACK && v->obj)
        o.obj = lin_stack_grab((LinStack *)v->obj);
    else if (v->kind == VAL_QUEUE && v->obj)
        o.obj = lin_queue_grab((LinQueue *)v->obj);
    return o;
}

static Value make_int(int x) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_INT;
    v.i = x;
    return v;
}

static Value make_float(double x) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_FLOAT;
    v.f = x;
    return v;
}

static Value make_bool(int b) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_BOOL;
    v.i = b ? 1 : 0;
    return v;
}

static Value make_string_owned(char *s) {
    Value v;
    v.kind = VAL_STRING;
    v.i = 0;
    v.f = 0;
    v.s = s;
    v.obj = NULL;
    return v;
}

static Value make_graph_val(LinGraph *g) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_GRAPH;
    v.obj = g;
    return v;
}

static Value make_tree_val(LinTree *t) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_TREE;
    v.obj = t;
    return v;
}

static Value make_dsu_val(LinDSU *d) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_DSU;
    v.obj = d;
    return v;
}

static Value make_matrix_val(LinMatrix *m) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_MATRIX;
    v.obj = m;
    return v;
}

static Value make_oset_val(LinOSet *s) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_ORDERED_SET;
    v.obj = s;
    return v;
}

static Value make_segtree_val(LinSegTree *st) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_RANGE_TREE;
    v.obj = st;
    return v;
}

static Value make_stack_val(LinStack *s) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_STACK;
    v.obj = s;
    return v;
}

static Value make_queue_val(LinQueue *q) {
    Value v;
    memset(&v, 0, sizeof(v));
    v.kind = VAL_QUEUE;
    v.obj = q;
    return v;
}

static int truthy(Value v) {
    switch (v.kind) {
        case VAL_INT:
        case VAL_BOOL:
            return v.i != 0;
        case VAL_FLOAT:
            return v.f != 0.0;
        case VAL_STRING:
            return v.s && v.s[0] != '\0';
        case VAL_GRAPH:
        case VAL_TREE:
        case VAL_DSU:
        case VAL_MATRIX:
        case VAL_ORDERED_SET:
        case VAL_RANGE_TREE:
        case VAL_STACK:
        case VAL_QUEUE:
            return v.obj != NULL;
        default:
            return 0;
    }
}

static void env_push(void) {
    Env *e = (Env *)malloc(sizeof(Env));
    if (!e) exit(EXIT_FAILURE);
    e->head = NULL;
    e->parent = env_current;
    env_current = e;
}

static void env_pop(void) {
    Env *e = env_current;
    if (!e) return;
    VarNode *n = e->head;
    while (n) {
        VarNode *nx = n->next;
        value_clear(&n->val);
        free(n);
        n = nx;
    }
    env_current = e->parent;
    free(e);
}

static Value *env_lookup(const char *name) {
    for (Env *e = env_current; e; e = e->parent) {
        for (VarNode *n = e->head; n; n = n->next) {
            if (strcmp(n->name, name) == 0)
                return &n->val;
        }
    }
    return NULL;
}

static void env_declare(const char *name, Value v) {
    VarNode *n = (VarNode *)malloc(sizeof(VarNode));
    if (!n) exit(EXIT_FAILURE);
    strncpy(n->name, name, MAX_ID_LENGTH - 1);
    n->name[MAX_ID_LENGTH - 1] = '\0';
    n->val = value_dup(&v);
    value_clear(&v);
    n->next = env_current->head;
    env_current->head = n;
}

static void env_assign(const char *name, Value v) {
    Value *existing = env_lookup(name);
    if (existing) {
        value_clear(existing);
        *existing = value_dup(&v);
        value_clear(&v);
        return;
    }
    fprintf(stderr, "Runtime error: assignment to undeclared '%s'\n", name);
    value_clear(&v);
}

static Value default_for_type(DataType t) {
    switch (t) {
        case TYPE_FLOAT:
            return make_float(0.0);
        case TYPE_BOOL:
            return make_bool(0);
        case TYPE_STRING:
            return make_string_owned(strdup(""));
        case TYPE_CHAR:
            return make_int(0);
        case TYPE_GRAPH:
            return make_graph_val(lin_graph_new(0));
        case TYPE_TREE:
            return make_tree_val(lin_tree_new(0));
        case TYPE_RANGE_TREE:
            return make_segtree_val(lin_segtree_new(1));
        case TYPE_DSU:
            return make_dsu_val(lin_dsu_new(0));
        case TYPE_MATRIX:
            return make_matrix_val(lin_matrix_new(0, 0));
        case TYPE_ORDERED_SET:
            return make_oset_val(lin_oset_new());
        default:
            return make_int(0);
    }
}

static void promote_binary(Value *a, Value *b, int *is_float) {
    *is_float = 0;
    if (a->kind == VAL_FLOAT || b->kind == VAL_FLOAT) {
        *is_float = 1;
        if (a->kind == VAL_INT) {
            a->f = (double)a->i;
            a->kind = VAL_FLOAT;
        }
        if (b->kind == VAL_INT) {
            b->f = (double)b->i;
            b->kind = VAL_FLOAT;
        }
    }
}

static int val_as_int(Value v) {
    if (v.kind == VAL_FLOAT) return (int)v.f;
    if (v.kind == VAL_BOOL || v.kind == VAL_INT) return v.i;
    return 0;
}

static double val_as_double(Value v) {
    if (v.kind == VAL_FLOAT) return v.f;
    if (v.kind == VAL_INT || v.kind == VAL_BOOL) return (double)v.i;
    return 0.0;
}

static Value eval_expr(ASTNode *n);
static Value eval_func_call(ASTNode *n); /* defined after eval_expr */

static ASTNode *find_function_decl(const char *name) {
    for (ASTNode *f = g_function_decls; f; f = f->next) {
        if (f->type == NODE_FUNC_DECL && f->name && strcmp(f->name, name) == 0)
            return f;
    }
    return NULL;
}

static char *strip_string_quotes(const char *raw) {
    size_t len = strlen(raw);
    if (len >= 2 && raw[0] == '"' && raw[len - 1] == '"') {
        char *out = (char *)malloc(len - 1);
        if (!out) exit(EXIT_FAILURE);
        strncpy(out, raw + 1, len - 2);
        out[len - 2] = '\0';
        return out;
    }
    return strdup(raw);
}

static Value eval_expr(ASTNode *n) {
    if (!n) return make_int(0);

    switch (n->type) {
        case NODE_LITERAL_INT:
            return make_int(n->int_val);
        case NODE_LITERAL_FLOAT:
            return make_float((double)n->float_val);
        case NODE_LITERAL_BOOL:
            return make_bool(n->int_val);
        case NODE_LITERAL_CHAR:
            return make_int(n->int_val);
        case NODE_LITERAL_STRING: {
            char *t = strip_string_quotes(n->name ? n->name : "");
            return make_string_owned(t);
        }
        case NODE_IDENTIFIER: {
            Value *v = env_lookup(n->name);
            if (!v) {
                fprintf(stderr, "Runtime error: undefined variable '%s'\n", n->name);
                return make_int(0);
            }
            return value_dup(v);
        }
        case NODE_UNARY_OP: {
            Value a = eval_expr(n->left);
            if (strcmp(n->name, "!") == 0) {
                int t = !truthy(a);
                value_clear(&a);
                return make_bool(t);
            }
            if (strcmp(n->name, "-") == 0) {
                if (a.kind == VAL_FLOAT) {
                    a.f = -a.f;
                    return a;
                }
                a.i = -a.i;
                return a;
            }
            value_clear(&a);
            return make_int(0);
        }
        case NODE_BINARY_OP: {
            Value L = eval_expr(n->left);
            Value R = eval_expr(n->right);
            if (strcmp(n->name, "&&") == 0) {
                int t = truthy(L) && truthy(R);
                value_clear(&L);
                value_clear(&R);
                return make_bool(t);
            }
            if (strcmp(n->name, "||") == 0) {
                int t = truthy(L) || truthy(R);
                value_clear(&L);
                value_clear(&R);
                return make_bool(t);
            }
            int isf = 0;
            promote_binary(&L, &R, &isf);
            if (strcmp(n->name, "+") == 0 && L.kind == VAL_STRING && R.kind == VAL_STRING) {
                size_t ln = strlen(L.s ? L.s : "");
                size_t rn = strlen(R.s ? R.s : "");
                char *cat = (char *)malloc(ln + rn + 1);
                if (!cat) exit(EXIT_FAILURE);
                strcpy(cat, L.s ? L.s : "");
                strcat(cat, R.s ? R.s : "");
                value_clear(&L);
                value_clear(&R);
                return make_string_owned(cat);
            }
            if (isf) {
                double x = L.f, y = R.f, res = 0;
                if (strcmp(n->name, "+") == 0) res = x + y;
                else if (strcmp(n->name, "-") == 0) res = x - y;
                else if (strcmp(n->name, "*") == 0) res = x * y;
                else if (strcmp(n->name, "/") == 0) res = y != 0.0 ? x / y : 0.0;
                else if (strcmp(n->name, "%") == 0) res = fmod(x, y);
                else if (strcmp(n->name, "==") == 0) {
                    value_clear(&L);
                    value_clear(&R);
                    return make_bool(x == y);
                } else if (strcmp(n->name, "!=") == 0) {
                    value_clear(&L);
                    value_clear(&R);
                    return make_bool(x != y);
                } else if (strcmp(n->name, "<") == 0) {
                    value_clear(&L);
                    value_clear(&R);
                    return make_bool(x < y);
                } else if (strcmp(n->name, ">") == 0) {
                    value_clear(&L);
                    value_clear(&R);
                    return make_bool(x > y);
                } else if (strcmp(n->name, "<=") == 0) {
                    value_clear(&L);
                    value_clear(&R);
                    return make_bool(x <= y);
                } else if (strcmp(n->name, ">=") == 0) {
                    value_clear(&L);
                    value_clear(&R);
                    return make_bool(x >= y);
                }
                value_clear(&L);
                value_clear(&R);
                return make_float(res);
            }
            int li = L.i, ri = R.i;
            value_clear(&L);
            value_clear(&R);
            if (strcmp(n->name, "+") == 0) return make_int(li + ri);
            if (strcmp(n->name, "-") == 0) return make_int(li - ri);
            if (strcmp(n->name, "*") == 0) return make_int(li * ri);
            if (strcmp(n->name, "/") == 0) return make_int(ri != 0 ? li / ri : 0);
            if (strcmp(n->name, "%") == 0) return make_int(ri != 0 ? li % ri : 0);
            if (strcmp(n->name, "==") == 0) return make_bool(li == ri);
            if (strcmp(n->name, "!=") == 0) return make_bool(li != ri);
            if (strcmp(n->name, "<") == 0) return make_bool(li < ri);
            if (strcmp(n->name, ">") == 0) return make_bool(li > ri);
            if (strcmp(n->name, "<=") == 0) return make_bool(li <= ri);
            if (strcmp(n->name, ">=") == 0) return make_bool(li >= ri);
            return make_int(0);
        }
        case NODE_ASSIGN: {
            ASTNode *id = n->left;
            if (!id || id->type != NODE_IDENTIFIER || !id->name)
                return make_int(0);
            Value v = eval_expr(n->right);
            env_assign(id->name, v);
            return value_dup(&v);
        }
        case NODE_FUNC_CALL:
            return eval_func_call(n);
        default:
            return make_int(0);
    }
}

static EvalResult eval_stmt(ASTNode *n);

static EvalResult eval_stmt_or_block(ASTNode *n) {
    if (!n) return EV_OK;
    if (n->type == NODE_BLOCK) {
        env_push();
        for (ASTNode *s = n->left; s; s = s->next) {
            EvalResult r = eval_stmt(s);
            if (r != EV_OK) {
                env_pop();
                return r;
            }
        }
        env_pop();
        return EV_OK;
    }
    return eval_stmt(n);
}

static EvalResult eval_stmt(ASTNode *n) {
    if (!n) return EV_OK;

    switch (n->type) {
        case NODE_EMPTY:
            return EV_OK;
        case NODE_VAR_DECL: {
            Symbol *sym = lookup_symbol(n->name);
            DataType t = sym ? sym->type : TYPE_INT;
            Value init;
            if (n->left)
                init = eval_expr(n->left);
            else
                init = default_for_type(t);
            env_declare(n->name, init);
            return EV_OK;
        }
        case NODE_IF: {
            Value c = eval_expr(n->left);
            int t = truthy(c);
            value_clear(&c);
            if (t)
                return eval_stmt_or_block(n->middle ? n->middle : n->right);
            if (n->middle)
                return eval_stmt_or_block(n->right);
            return EV_OK;
        }
        case NODE_WHILE: {
            while (1) {
                Value c = eval_expr(n->left);
                if (!truthy(c)) {
                    value_clear(&c);
                    break;
                }
                value_clear(&c);
                EvalResult r = eval_stmt_or_block(n->right);
                if (r == EV_BREAK) break;
                if (r == EV_CONTINUE) continue;
                if (r == EV_RETURN) return EV_RETURN;
            }
            return EV_OK;
        }
        case NODE_FOR: {
            if (n->left)
                eval_stmt(n->left);
            while (1) {
                Value c = eval_expr(n->middle);
                if (!truthy(c)) {
                    value_clear(&c);
                    break;
                }
                value_clear(&c);
                EvalResult r = eval_stmt_or_block(n->body);
                if (r == EV_BREAK) break;
                if (r == EV_RETURN) return EV_RETURN;
                if (r == EV_CONTINUE) {
                    eval_expr(n->right);
                    continue;
                }
                eval_expr(n->right);
            }
            return EV_OK;
        }
        case NODE_FUNC_CALL:
            eval_expr(n);
            return EV_OK;
        case NODE_BREAK:
            return EV_BREAK;
        case NODE_CONTINUE:
            return EV_CONTINUE;
        case NODE_RETURN:
            if (g_has_return)
                value_clear(&g_return_value);
            if (n->left)
                g_return_value = eval_expr(n->left);
            else
                g_return_value = make_int(0);
            g_has_return = 1;
            return EV_RETURN;
        case NODE_BLOCK:
            return eval_stmt_or_block(n);
        default:
            eval_expr(n);
            return EV_OK;
    }
}

static Value eval_arg(ASTNode *call_args, int idx) {
    ASTNode *a = call_args;
    while (idx-- > 0 && a) a = a->next;
    if (!a) return make_int(0);
    return eval_expr(a);
}

static Value eval_func_call(ASTNode *n) {
    const char *fn = n->name ? n->name : "";
    ASTNode *args = n->call_args ? n->call_args : n->left;

    if (!strcmp(fn, "MAHI_write")) {
        Value v = eval_expr(args);
        switch (v.kind) {
            case VAL_INT: printf("%d", v.i); break;
            case VAL_FLOAT: printf("%g", v.f); break;
            case VAL_BOOL: printf("%s", v.i ? "true" : "false"); break;
            case VAL_STRING: printf("%s", v.s ? v.s : ""); break;
            default: break;
        }
        printf("\n");
        value_clear(&v);
        return make_int(0);
    }
    if (!strcmp(fn, "MAHI_read")) {
        ASTNode *id = args;
        if (!id || id->type != NODE_IDENTIFIER || !id->name) return make_int(0);
        Symbol *sym = lookup_symbol(id->name);
        Value got;
        memset(&got, 0, sizeof(got));
        if (sym && sym->type == TYPE_FLOAT) {
            double t;
            if (scanf("%lf", &t) != 1) t = 0.0;
            got = make_float(t);
        } else if (sym && sym->type == TYPE_BOOL) {
            int t;
            if (scanf("%d", &t) != 1) t = 0;
            got = make_bool(t != 0);
        } else if (sym && sym->type == TYPE_STRING) {
            char buf[1024];
            if (scanf("%1023s", buf) != 1) buf[0] = '\0';
            got = make_string_owned(strdup(buf));
        } else {
            int t;
            if (scanf("%d", &t) != 1) t = 0;
            got = make_int(t);
        }
        env_assign(id->name, got);
        return make_int(0);
    }
    if (!strcmp(fn, "MAHI_sort") || !strcmp(fn, "MAHI_push")) {
        if (args) {
            Value v = eval_expr(args);
            value_clear(&v);
        }
        return make_int(0);
    }

    if (!strcmp(fn, "graph_new")) {
        int nv = val_as_int(eval_arg(args, 0));
        return make_graph_val(lin_graph_new(nv));
    }
    if (!strcmp(fn, "graph_add_edge")) {
        Value g = eval_arg(args, 0);
        int u = val_as_int(eval_arg(args, 1));
        int v = val_as_int(eval_arg(args, 2));
        if (g.kind == VAL_GRAPH && g.obj)
            lin_graph_add_edge((LinGraph *)g.obj, u, v);
        value_clear(&g);
        return make_int(0);
    }
    if (!strcmp(fn, "graph_shortest_path")) {
        Value g = eval_arg(args, 0);
        int s = val_as_int(eval_arg(args, 1));
        int t = val_as_int(eval_arg(args, 2));
        int d = -1;
        if (g.kind == VAL_GRAPH && g.obj)
            d = lin_graph_shortest_path((LinGraph *)g.obj, s, t);
        value_clear(&g);
        return make_int(d);
    }
    if (!strcmp(fn, "graph_connected")) {
        Value g = eval_arg(args, 0);
        int s = val_as_int(eval_arg(args, 1));
        int t = val_as_int(eval_arg(args, 2));
        int r = 0;
        if (g.kind == VAL_GRAPH && g.obj)
            r = lin_graph_connected((LinGraph *)g.obj, s, t);
        value_clear(&g);
        return make_int(r);
    }
    if (!strcmp(fn, "graph_dfs_count")) {
        Value g = eval_arg(args, 0);
        int st = val_as_int(eval_arg(args, 1));
        int c = 0;
        if (g.kind == VAL_GRAPH && g.obj)
            c = lin_graph_dfs_count((LinGraph *)g.obj, st);
        value_clear(&g);
        return make_int(c);
    }

    if (!strcmp(fn, "tree_new")) {
        int nv = val_as_int(eval_arg(args, 0));
        return make_tree_val(lin_tree_new(nv));
    }
    if (!strcmp(fn, "tree_set_parent")) {
        Value t = eval_arg(args, 0);
        int node = val_as_int(eval_arg(args, 1));
        int par = val_as_int(eval_arg(args, 2));
        if (t.kind == VAL_TREE && t.obj)
            lin_tree_set_parent((LinTree *)t.obj, node, par);
        value_clear(&t);
        return make_int(0);
    }
    if (!strcmp(fn, "tree_lca")) {
        Value t = eval_arg(args, 0);
        int a = val_as_int(eval_arg(args, 1));
        int b = val_as_int(eval_arg(args, 2));
        int l = -1;
        if (t.kind == VAL_TREE && t.obj)
            l = lin_tree_lca((LinTree *)t.obj, a, b);
        value_clear(&t);
        return make_int(l);
    }
    if (!strcmp(fn, "tree_depth")) {
        Value t = eval_arg(args, 0);
        int v = val_as_int(eval_arg(args, 1));
        int d = 0;
        if (t.kind == VAL_TREE && t.obj)
            d = lin_tree_depth((LinTree *)t.obj, v);
        value_clear(&t);
        return make_int(d);
    }

    if (!strcmp(fn, "dsu_new")) {
        int nv = val_as_int(eval_arg(args, 0));
        return make_dsu_val(lin_dsu_new(nv));
    }
    if (!strcmp(fn, "dsu_union")) {
        Value d = eval_arg(args, 0);
        int a = val_as_int(eval_arg(args, 1));
        int b = val_as_int(eval_arg(args, 2));
        if (d.kind == VAL_DSU && d.obj)
            lin_dsu_union((LinDSU *)d.obj, a, b);
        value_clear(&d);
        return make_int(0);
    }
    if (!strcmp(fn, "dsu_find")) {
        Value d = eval_arg(args, 0);
        int x = val_as_int(eval_arg(args, 1));
        int r = -1;
        if (d.kind == VAL_DSU && d.obj)
            r = lin_dsu_find((LinDSU *)d.obj, x);
        value_clear(&d);
        return make_int(r);
    }
    if (!strcmp(fn, "dsu_same")) {
        Value d = eval_arg(args, 0);
        int a = val_as_int(eval_arg(args, 1));
        int b = val_as_int(eval_arg(args, 2));
        int r = 0;
        if (d.kind == VAL_DSU && d.obj)
            r = lin_dsu_same((LinDSU *)d.obj, a, b);
        value_clear(&d);
        return make_int(r);
    }

    if (!strcmp(fn, "matrix_new")) {
        int r = val_as_int(eval_arg(args, 0));
        int c = val_as_int(eval_arg(args, 1));
        return make_matrix_val(lin_matrix_new(r, c));
    }
    if (!strcmp(fn, "matrix_get")) {
        Value m = eval_arg(args, 0);
        int i = val_as_int(eval_arg(args, 1));
        int j = val_as_int(eval_arg(args, 2));
        double x = 0;
        if (m.kind == VAL_MATRIX && m.obj)
            x = lin_matrix_get((LinMatrix *)m.obj, i, j);
        value_clear(&m);
        return make_float(x);
    }
    if (!strcmp(fn, "matrix_set")) {
        Value m = eval_arg(args, 0);
        int i = val_as_int(eval_arg(args, 1));
        int j = val_as_int(eval_arg(args, 2));
        double x = val_as_double(eval_arg(args, 3));
        if (m.kind == VAL_MATRIX && m.obj)
            lin_matrix_set((LinMatrix *)m.obj, i, j, x);
        value_clear(&m);
        return make_int(0);
    }
    if (!strcmp(fn, "matrix_add")) {
        Value a = eval_arg(args, 0);
        Value b = eval_arg(args, 1);
        LinMatrix *r = NULL;
        if (a.kind == VAL_MATRIX && a.obj && b.kind == VAL_MATRIX && b.obj)
            r = lin_matrix_add((LinMatrix *)a.obj, (LinMatrix *)b.obj);
        value_clear(&a);
        value_clear(&b);
        return r ? make_matrix_val(r) : make_int(0);
    }
    if (!strcmp(fn, "matrix_mul")) {
        Value a = eval_arg(args, 0);
        Value b = eval_arg(args, 1);
        LinMatrix *r = NULL;
        if (a.kind == VAL_MATRIX && a.obj && b.kind == VAL_MATRIX && b.obj)
            r = lin_matrix_mul((LinMatrix *)a.obj, (LinMatrix *)b.obj);
        value_clear(&a);
        value_clear(&b);
        return r ? make_matrix_val(r) : make_int(0);
    }
    if (!strcmp(fn, "matrix_transpose")) {
        Value m = eval_arg(args, 0);
        LinMatrix *r = NULL;
        if (m.kind == VAL_MATRIX && m.obj)
            r = lin_matrix_transpose((LinMatrix *)m.obj);
        value_clear(&m);
        return r ? make_matrix_val(r) : make_int(0);
    }
    if (!strcmp(fn, "matrix_identity")) {
        int n = val_as_int(eval_arg(args, 0));
        LinMatrix *r = lin_matrix_identity(n);
        return r ? make_matrix_val(r) : make_int(0);
    }
    if (!strcmp(fn, "matrix_rows")) {
        Value m = eval_arg(args, 0);
        int r = 0;
        if (m.kind == VAL_MATRIX && m.obj)
            r = lin_matrix_rows((LinMatrix *)m.obj);
        value_clear(&m);
        return make_int(r);
    }
    if (!strcmp(fn, "matrix_cols")) {
        Value m = eval_arg(args, 0);
        int c = 0;
        if (m.kind == VAL_MATRIX && m.obj)
            c = lin_matrix_cols((LinMatrix *)m.obj);
        value_clear(&m);
        return make_int(c);
    }

    if (!strcmp(fn, "oset_new")) {
        return make_oset_val(lin_oset_new());
    }
    if (!strcmp(fn, "oset_insert")) {
        Value s = eval_arg(args, 0);
        int x = val_as_int(eval_arg(args, 1));
        if (s.kind == VAL_ORDERED_SET && s.obj)
            lin_oset_insert((LinOSet *)s.obj, x);
        value_clear(&s);
        return make_int(0);
    }
    if (!strcmp(fn, "oset_erase")) {
        Value s = eval_arg(args, 0);
        int x = val_as_int(eval_arg(args, 1));
        if (s.kind == VAL_ORDERED_SET && s.obj)
            lin_oset_erase((LinOSet *)s.obj, x);
        value_clear(&s);
        return make_int(0);
    }
    if (!strcmp(fn, "oset_size")) {
        Value s = eval_arg(args, 0);
        int sz = 0;
        if (s.kind == VAL_ORDERED_SET && s.obj)
            sz = lin_oset_size((LinOSet *)s.obj);
        value_clear(&s);
        return make_int(sz);
    }
    if (!strcmp(fn, "oset_contains")) {
        Value s = eval_arg(args, 0);
        int x = val_as_int(eval_arg(args, 1));
        int r = 0;
        if (s.kind == VAL_ORDERED_SET && s.obj)
            r = lin_oset_contains((LinOSet *)s.obj, x);
        value_clear(&s);
        return make_int(r);
    }
    if (!strcmp(fn, "oset_nth")) {
        Value s = eval_arg(args, 0);
        int k = val_as_int(eval_arg(args, 1));
        int r = -1;
        if (s.kind == VAL_ORDERED_SET && s.obj)
            r = lin_oset_nth((LinOSet *)s.obj, k);
        value_clear(&s);
        return make_int(r);
    }

    if (!strcmp(fn, "segtree_new")) {
        int n = val_as_int(eval_arg(args, 0));
        if (n < 1) n = 1;
        return make_segtree_val(lin_segtree_new(n));
    }
    if (!strcmp(fn, "segtree_set")) {
        Value st = eval_arg(args, 0);
        int i = val_as_int(eval_arg(args, 1));
        int v = val_as_int(eval_arg(args, 2));
        if (st.kind == VAL_RANGE_TREE && st.obj)
            lin_segtree_set((LinSegTree *)st.obj, i, v);
        value_clear(&st);
        return make_int(0);
    }
    if (!strcmp(fn, "segtree_sum")) {
        Value st = eval_arg(args, 0);
        int l = val_as_int(eval_arg(args, 1));
        int r = val_as_int(eval_arg(args, 2));
        int s = 0;
        if (st.kind == VAL_RANGE_TREE && st.obj)
            s = lin_segtree_sum((LinSegTree *)st.obj, l, r);
        value_clear(&st);
        return make_int(s);
    }
    if (!strcmp(fn, "segtree_min")) {
        Value st = eval_arg(args, 0);
        int l = val_as_int(eval_arg(args, 1));
        int r = val_as_int(eval_arg(args, 2));
        int m = INT_MAX;
        if (st.kind == VAL_RANGE_TREE && st.obj)
            m = lin_segtree_min((LinSegTree *)st.obj, l, r);
        value_clear(&st);
        return make_int(m);
    }

    if (!strcmp(fn, "stack_new")) {
        return make_stack_val(lin_stack_new());
    }
    if (!strcmp(fn, "stack_push")) {
        Value s = eval_arg(args, 0);
        int x = val_as_int(eval_arg(args, 1));
        if (s.kind == VAL_STACK && s.obj)
            lin_stack_push((LinStack *)s.obj, x);
        value_clear(&s);
        return make_int(0);
    }
    if (!strcmp(fn, "stack_pop")) {
        Value s = eval_arg(args, 0);
        int r = 0;
        if (s.kind == VAL_STACK && s.obj)
            r = lin_stack_pop((LinStack *)s.obj);
        value_clear(&s);
        return make_int(r);
    }
    if (!strcmp(fn, "stack_top")) {
        Value s = eval_arg(args, 0);
        int r = 0;
        if (s.kind == VAL_STACK && s.obj)
            r = lin_stack_top((LinStack *)s.obj);
        value_clear(&s);
        return make_int(r);
    }
    if (!strcmp(fn, "stack_size")) {
        Value s = eval_arg(args, 0);
        int r = 0;
        if (s.kind == VAL_STACK && s.obj)
            r = lin_stack_size((LinStack *)s.obj);
        value_clear(&s);
        return make_int(r);
    }
    if (!strcmp(fn, "stack_empty")) {
        Value s = eval_arg(args, 0);
        int r = 1;
        if (s.kind == VAL_STACK && s.obj)
            r = lin_stack_empty((LinStack *)s.obj);
        value_clear(&s);
        return make_int(r);
    }

    if (!strcmp(fn, "queue_new")) {
        return make_queue_val(lin_queue_new());
    }
    if (!strcmp(fn, "queue_push")) {
        Value q = eval_arg(args, 0);
        int x = val_as_int(eval_arg(args, 1));
        if (q.kind == VAL_QUEUE && q.obj)
            lin_queue_push((LinQueue *)q.obj, x);
        value_clear(&q);
        return make_int(0);
    }
    if (!strcmp(fn, "queue_pop")) {
        Value q = eval_arg(args, 0);
        int r = 0;
        if (q.kind == VAL_QUEUE && q.obj)
            r = lin_queue_pop((LinQueue *)q.obj);
        value_clear(&q);
        return make_int(r);
    }
    if (!strcmp(fn, "queue_front")) {
        Value q = eval_arg(args, 0);
        int r = 0;
        if (q.kind == VAL_QUEUE && q.obj)
            r = lin_queue_front((LinQueue *)q.obj);
        value_clear(&q);
        return make_int(r);
    }
    if (!strcmp(fn, "queue_size")) {
        Value q = eval_arg(args, 0);
        int r = 0;
        if (q.kind == VAL_QUEUE && q.obj)
            r = lin_queue_size((LinQueue *)q.obj);
        value_clear(&q);
        return make_int(r);
    }
    if (!strcmp(fn, "queue_empty")) {
        Value q = eval_arg(args, 0);
        int r = 1;
        if (q.kind == VAL_QUEUE && q.obj)
            r = lin_queue_empty((LinQueue *)q.obj);
        value_clear(&q);
        return make_int(r);
    }

    {
        ASTNode *decl = find_function_decl(fn);
        if (decl) {
            env_push();

            ASTNode *p = decl->left;
            ASTNode *a = args;
            while (p) {
                Value av = a ? eval_expr(a) : make_int(0);
                env_declare(p->name ? p->name : "", av);
                p = p->next;
                if (a) a = a->next;
            }

            int prev_has = g_has_return;
            Value prev_ret;
            memset(&prev_ret, 0, sizeof(prev_ret));
            if (prev_has)
                prev_ret = value_dup(&g_return_value);

            g_has_return = 0;
            EvalResult r = eval_stmt_or_block(decl->right);

            Value out = make_int(0);
            if (r == EV_RETURN && g_has_return)
                out = value_dup(&g_return_value);

            if (g_has_return)
                value_clear(&g_return_value);

            if (prev_has) {
                g_return_value = prev_ret;
                g_has_return = 1;
            } else {
                memset(&g_return_value, 0, sizeof(g_return_value));
                g_has_return = 0;
            }

            env_pop();
            return out;
        }
    }

    fprintf(stderr, "Runtime: unknown call '%s'\n", fn);
    return make_int(0);
}

void interpret(ASTNode *root) {
    if (!root || root->type != NODE_PROGRAM) {
        fprintf(stderr, "Nothing to run.\n");
        return;
    }

    g_function_decls = root->middle;
    g_has_return = 0;
    memset(&g_return_value, 0, sizeof(g_return_value));

    eval_stmt_or_block(root->left);
}
