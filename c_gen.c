#include "c_gen.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int make_output_path(const char *src, char *dst, size_t dstsz) {
    if (!dst || dstsz == 0) return -1;

    if (!src || !*src) {
        snprintf(dst, dstsz, "output.generated.c");
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

    if (strlen(dst) + strlen(".generated.c") + 1 > dstsz) return -1;
    strcat(dst, ".generated.c");
    return 0;
}

static int is_ident_char(int c) {
    return isalnum((unsigned char)c) || c == '_';
}

static void replace_token(char *line, size_t cap, const char *token, const char *rep) {
    char out[8192];
    size_t token_len = strlen(token);
    size_t rep_len = strlen(rep);
    size_t i = 0, o = 0;

    while (line[i] != '\0' && o + 2 < sizeof(out)) {
        int left_ok = (i == 0) || !is_ident_char((unsigned char)line[i - 1]);
        int right_ok = !is_ident_char((unsigned char)line[i + token_len]);

        if (strncmp(&line[i], token, token_len) == 0 && left_ok && right_ok) {
            if (o + rep_len + 1 >= sizeof(out)) break;
            memcpy(&out[o], rep, rep_len);
            o += rep_len;
            i += token_len;
        } else {
            out[o++] = line[i++];
        }
    }

    out[o] = '\0';
    strncpy(line, out, cap - 1);
    line[cap - 1] = '\0';
}

static void replace_substr(char *line, size_t cap, const char *from, const char *to) {
    char out[8192];
    const char *p = line;
    size_t from_len = strlen(from);
    size_t to_len = strlen(to);
    size_t o = 0;

    while (*p && o + 2 < sizeof(out)) {
        const char *m = strstr(p, from);
        if (!m) {
            size_t rem = strlen(p);
            if (o + rem + 1 >= sizeof(out)) rem = sizeof(out) - o - 1;
            memcpy(&out[o], p, rem);
            o += rem;
            break;
        }

        size_t seg = (size_t)(m - p);
        if (o + seg + 1 >= sizeof(out)) break;
        memcpy(&out[o], p, seg);
        o += seg;

        if (o + to_len + 1 >= sizeof(out)) break;
        memcpy(&out[o], to, to_len);
        o += to_len;

        p = m + from_len;
    }

    out[o] = '\0';
    strncpy(line, out, cap - 1);
    line[cap - 1] = '\0';
}

static void transform_linear_line(char *line, size_t cap) {
    if (!line || !*line) return;

    replace_substr(line, cap, "START main", "int main(void)");
    replace_substr(line, cap, "} END", "}");

    /* Standalone END line removal */
    {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (strncmp(p, "END", 3) == 0) {
            char c = p[3];
            if (c == '\0' || c == '\n' || c == '\r') {
                line[0] = '\0';
                return;
            }
        }
    }

    /* function int foo(...)  -> int foo(...) */
    replace_substr(line, cap, "function ", "");

    /* type aliases for C */
    replace_token(line, cap, "string", "char*");
}

static int transpile_source_to_c(FILE *out, const char *source_path) {
    if (!source_path || !*source_path) return -4;

    FILE *in = fopen(source_path, "r");
    if (!in) return -5;

    char line[8192];
    while (fgets(line, sizeof(line), in)) {
        transform_linear_line(line, sizeof(line));
        if (line[0] == '\0') continue;
        fputs(line, out);
        if (line[strlen(line) - 1] != '\n') fputc('\n', out);
    }

    fclose(in);
    return 0;
}

int generate_c_code(ASTNode *root, const char *source_path,
                    char *out_path, size_t out_path_size) {
    if (!root || root->type != NODE_PROGRAM) return -1;

    char local_path[1024];
    if (make_output_path(source_path, local_path, sizeof(local_path)) != 0) return -2;

    FILE *out = fopen(local_path, "w");
    if (!out) return -3;

    fprintf(out, "/* Auto-generated C file from Linear source: %s */\n",
            source_path ? source_path : "<stdin>");
    fputs("#include <stdio.h>\n", out);
    fputs("#include <stdbool.h>\n", out);
    fputs("#include <string.h>\n", out);
    fputs("#include \"../ds_runtime.h\"\n\n", out);

    fputs("typedef LinGraph* Graph;\n", out);
    fputs("typedef LinTree* Tree;\n", out);
    fputs("typedef LinDSU* DSU;\n", out);
    fputs("typedef LinMatrix* Matrix;\n", out);
    fputs("typedef LinOSet* OrderedSet;\n", out);
    fputs("typedef LinSegTree* RangeTree;\n", out);
    fputs("typedef LinStack* Stack;\n", out);
    fputs("typedef LinQueue* Queue;\n\n", out);

    fputs("#define graph_new lin_graph_new\n", out);
    fputs("#define graph_add_edge lin_graph_add_edge\n", out);
    fputs("#define graph_shortest_path lin_graph_shortest_path\n", out);
    fputs("#define graph_connected lin_graph_connected\n", out);
    fputs("#define graph_dfs_count lin_graph_dfs_count\n", out);
    fputs("#define tree_new lin_tree_new\n", out);
    fputs("#define tree_set_parent lin_tree_set_parent\n", out);
    fputs("#define tree_lca lin_tree_lca\n", out);
    fputs("#define tree_depth lin_tree_depth\n", out);
    fputs("#define dsu_new lin_dsu_new\n", out);
    fputs("#define dsu_union lin_dsu_union\n", out);
    fputs("#define dsu_find lin_dsu_find\n", out);
    fputs("#define dsu_same lin_dsu_same\n", out);
    fputs("#define matrix_new lin_matrix_new\n", out);
    fputs("#define matrix_get lin_matrix_get\n", out);
    fputs("#define matrix_set lin_matrix_set\n", out);
    fputs("#define matrix_add lin_matrix_add\n", out);
    fputs("#define matrix_mul lin_matrix_mul\n", out);
    fputs("#define matrix_transpose lin_matrix_transpose\n", out);
    fputs("#define matrix_identity lin_matrix_identity\n", out);
    fputs("#define oset_new lin_oset_new\n", out);
    fputs("#define oset_insert lin_oset_insert\n", out);
    fputs("#define oset_erase lin_oset_erase\n", out);
    fputs("#define oset_size lin_oset_size\n", out);
    fputs("#define oset_contains lin_oset_contains\n", out);
    fputs("#define oset_nth lin_oset_nth\n", out);
    fputs("#define segtree_new lin_segtree_new\n", out);
    fputs("#define segtree_set lin_segtree_set\n", out);
    fputs("#define segtree_sum lin_segtree_sum\n", out);
    fputs("#define segtree_min lin_segtree_min\n", out);
    fputs("#define stack_new lin_stack_new\n", out);
    fputs("#define stack_push lin_stack_push\n", out);
    fputs("#define stack_pop lin_stack_pop\n", out);
    fputs("#define stack_top lin_stack_top\n", out);
    fputs("#define stack_size lin_stack_size\n", out);
    fputs("#define stack_empty lin_stack_empty\n", out);
    fputs("#define queue_new lin_queue_new\n", out);
    fputs("#define queue_push lin_queue_push\n", out);
    fputs("#define queue_pop lin_queue_pop\n", out);
    fputs("#define queue_front lin_queue_front\n", out);
    fputs("#define queue_size lin_queue_size\n", out);
    fputs("#define queue_empty lin_queue_empty\n\n", out);

    fputs("static void MAHI_write_int(int v){ printf(\"%d\\n\", v); }\n", out);
    fputs("static void MAHI_write_double(double v){ printf(\"%g\\n\", v); }\n", out);
    fputs("static void MAHI_write_bool(_Bool v){ printf(\"%s\\n\", v ? \"true\" : \"false\"); }\n", out);
    fputs("static void MAHI_write_str(const char* v){ printf(\"%s\\n\", v ? v : \"\"); }\n", out);
    fputs("#define MAHI_write(x) _Generic((x), int: MAHI_write_int, float: MAHI_write_double, double: MAHI_write_double, _Bool: MAHI_write_bool, char*: MAHI_write_str, const char*: MAHI_write_str, default: MAHI_write_int)(x)\n\n", out);

    int tx = transpile_source_to_c(out, source_path);
    if (tx != 0) {
        fclose(out);
        return tx;
    }

    fclose(out);

    if (out_path && out_path_size > 0) {
        snprintf(out_path, out_path_size, "%s", local_path);
    }

    return 0;
}
