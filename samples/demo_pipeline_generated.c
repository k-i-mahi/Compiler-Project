#include <stdio.h>
#include <stdbool.h>
#include "../ds_runtime.h"

static void write_int(int x) { printf("%d\n", x); }
static void write_float(double x) { printf("%g\n", x); }
static void write_bool(bool x) { printf("%s\n", x ? "true" : "false"); }
static void write_str(const char *s) { printf("%s\n", s); }

int main(void) {
    write_str("=== Linear Pipeline Demo Start ===");

    /* Primitive types and arithmetic */
    int a = 6;
    int b = 4;
    int c = a * b + 2;
    double pi = 3.14;
    bool ok = true;
    const char *title = "All-features demo";

    write_str(title);
    write_str("Value of c:");
    write_int(c);
    write_str("Float pi:");
    write_float(pi);
    write_str("Bool ok:");
    write_bool(ok);

    /* Conditionals */
    if (c > 20) {
        write_str("c is greater than 20");
    } else {
        write_str("c is not greater than 20");
    }

    /* Loop */
    int sum = 0;
    for (int i = 1; i <= 5; i = i + 1) {
        sum = sum + i;
    }
    write_str("Sum 1..5:");
    write_int(sum);

    /* While loop + continue/break */
    int w = 0;
    int wsum = 0;
    while (w < 6) {
        w = w + 1;
        if (w == 2) {
            continue;
        }
        if (w == 6) {
            break;
        }
        wsum = wsum + w;
    }
    write_str("While sum with continue/break:");
    write_int(wsum);

    /* DSU usage */
    LinDSU *d = lin_dsu_new(6);
    lin_dsu_union(d, 1, 2);
    lin_dsu_union(d, 2, 3);
    write_str("DSU same(1,3):");
    write_int(lin_dsu_same(d, 1, 3));

    /* Graph usage */
    LinGraph *g = lin_graph_new(4);
    lin_graph_add_edge(g, 0, 1);
    lin_graph_add_edge(g, 1, 2);
    write_str("Graph shortest path 0->2:");
    write_int(lin_graph_shortest_path(g, 0, 2));

    /* Tree usage */
    LinTree *t = lin_tree_new(5);
    lin_tree_set_parent(t, 1, 0);
    lin_tree_set_parent(t, 2, 0);
    lin_tree_set_parent(t, 3, 1);
    lin_tree_set_parent(t, 4, 1);
    write_str("Tree LCA(3,4):");
    write_int(lin_tree_lca(t, 3, 4));
    write_str("Tree depth(4):");
    write_int(lin_tree_depth(t, 4));

    /* RangeTree usage */
    LinSegTree *rt = lin_segtree_new(8);
    lin_segtree_set(rt, 0, 5);
    lin_segtree_set(rt, 1, 10);
    lin_segtree_set(rt, 2, 15);
    write_str("RangeTree sum [0,2]:");
    write_int(lin_segtree_sum(rt, 0, 2));
    write_str("RangeTree min [0,2]:");
    write_int(lin_segtree_min(rt, 0, 2));

    /* Matrix usage */
    LinMatrix *m = lin_matrix_new(2, 2);
    lin_matrix_set(m, 0, 0, 1.0);
    lin_matrix_set(m, 0, 1, 2.0);
    lin_matrix_set(m, 1, 0, 3.0);
    lin_matrix_set(m, 1, 1, 4.0);
    write_str("Matrix m[1][0]:");
    write_float(lin_matrix_get(m, 1, 0));

    LinMatrix *id = lin_matrix_identity(2);
    LinMatrix *mm = lin_matrix_mul(m, id);
    write_str("Matrix mul by identity, mm[0][1]:");
    write_float(lin_matrix_get(mm, 0, 1));

    /* Ordered set usage */
    LinOSet *os = lin_oset_new();
    lin_oset_insert(os, 30);
    lin_oset_insert(os, 10);
    lin_oset_insert(os, 20);
    write_str("OrderedSet 1st element (0-based):");
    write_int(lin_oset_nth(os, 1));
    write_str("OrderedSet contains 20:");
    write_int(lin_oset_contains(os, 20));

    /* Stack and Queue usage */
    LinStack *st = lin_stack_new();
    lin_stack_push(st, 100);
    lin_stack_push(st, 200);
    write_str("Stack top:");
    write_int(lin_stack_top(st));
    write_str("Stack size:");
    write_int(lin_stack_size(st));

    LinQueue *q = lin_queue_new();
    lin_queue_push(q, 7);
    lin_queue_push(q, 9);
    write_str("Queue front:");
    write_int(lin_queue_front(q));
    write_str("Queue size:");
    write_int(lin_queue_size(q));

    write_str("=== Linear Pipeline Demo End ===");

    /* cleanup */
    lin_dsu_free(d);
    lin_graph_free(g);
    lin_tree_free(t);
    lin_segtree_free(rt);
    lin_matrix_free(m);
    lin_matrix_free(id);
    lin_matrix_free(mm);
    lin_oset_free(os);
    lin_stack_free(st);
    lin_queue_free(q);

    return 0;
}
