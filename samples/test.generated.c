/* Auto-generated C file from Linear source: .\samples\test.linear */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../ds_runtime.h"

typedef LinGraph* Graph;
typedef LinTree* Tree;
typedef LinDSU* DSU;
typedef LinMatrix* Matrix;
typedef LinOSet* OrderedSet;
typedef LinSegTree* RangeTree;
typedef LinStack* Stack;
typedef LinQueue* Queue;

#define graph_new lin_graph_new
#define graph_add_edge lin_graph_add_edge
#define graph_shortest_path lin_graph_shortest_path
#define graph_connected lin_graph_connected
#define graph_dfs_count lin_graph_dfs_count
#define tree_new lin_tree_new
#define tree_set_parent lin_tree_set_parent
#define tree_lca lin_tree_lca
#define tree_depth lin_tree_depth
#define dsu_new lin_dsu_new
#define dsu_union lin_dsu_union
#define dsu_find lin_dsu_find
#define dsu_same lin_dsu_same
#define matrix_new lin_matrix_new
#define matrix_get lin_matrix_get
#define matrix_set lin_matrix_set
#define matrix_add lin_matrix_add
#define matrix_mul lin_matrix_mul
#define matrix_transpose lin_matrix_transpose
#define matrix_identity lin_matrix_identity
#define oset_new lin_oset_new
#define oset_insert lin_oset_insert
#define oset_erase lin_oset_erase
#define oset_size lin_oset_size
#define oset_contains lin_oset_contains
#define oset_nth lin_oset_nth
#define segtree_new lin_segtree_new
#define segtree_set lin_segtree_set
#define segtree_sum lin_segtree_sum
#define segtree_min lin_segtree_min
#define stack_new lin_stack_new
#define stack_push lin_stack_push
#define stack_pop lin_stack_pop
#define stack_top lin_stack_top
#define stack_size lin_stack_size
#define stack_empty lin_stack_empty
#define queue_new lin_queue_new
#define queue_push lin_queue_push
#define queue_pop lin_queue_pop
#define queue_front lin_queue_front
#define queue_size lin_queue_size
#define queue_empty lin_queue_empty

static void MAHI_write_int(int v){ printf("%d\n", v); }
static void MAHI_write_double(double v){ printf("%g\n", v); }
static void MAHI_write_bool(_Bool v){ printf("%s\n", v ? "true" : "false"); }
static void MAHI_write_str(const char* v){ printf("%s\n", v ? v : ""); }
#define MAHI_write(x) _Generic((x), int: MAHI_write_int, float: MAHI_write_double, double: MAHI_write_double, _Bool: MAHI_write_bool, char*: MAHI_write_str, const char*: MAHI_write_str, default: MAHI_write_int)(x)

int main(void) {
    MAHI_write("=== Linear Pipeline Demo Start ===");

    // Primitive types and arithmetic
    int a = 6;
    int b = 4;
    int c = a * b + 2;
    float pi = 3.14;
    bool ok = true;
    char* title = "All-features demo";

    MAHI_write(title);
    MAHI_write("Value of c:");
    MAHI_write(c);
    MAHI_write("Float pi:");
    MAHI_write(pi);
    MAHI_write("Bool ok:");
    MAHI_write(ok);

    // Conditionals
    if (c > 20) {
        MAHI_write("c is greater than 20");
    } else {
        MAHI_write("c is not greater than 20");
    }

    // Loop
    int sum = 0;
    for (int i = 1; i <= 5; i = i + 1) {
        sum = sum + i;
    }
    MAHI_write("Sum 1..5:");
    MAHI_write(sum);

    // While loop + continue/break
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
    MAHI_write("While sum with continue/break:");
    MAHI_write(wsum);

    // DSU usage
    DSU d = dsu_new(6);
    dsu_union(d, 1, 2);
    dsu_union(d, 2, 3);
    MAHI_write("DSU same(1,3):");
    MAHI_write(dsu_same(d, 1, 3));

    // Graph usage
    Graph g = graph_new(4);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    MAHI_write("Graph shortest path 0->2:");
    MAHI_write(graph_shortest_path(g, 0, 2));

    // Tree usage
    Tree t = tree_new(5);
    tree_set_parent(t, 1, 0);
    tree_set_parent(t, 2, 0);
    tree_set_parent(t, 3, 1);
    tree_set_parent(t, 4, 1);
    MAHI_write("Tree LCA(3,4):");
    MAHI_write(tree_lca(t, 3, 4));
    MAHI_write("Tree depth(4):");
    MAHI_write(tree_depth(t, 4));

    // RangeTree usage
    RangeTree rt = segtree_new(8);
    segtree_set(rt, 0, 5);
    segtree_set(rt, 1, 10);
    segtree_set(rt, 2, 15);
    MAHI_write("RangeTree sum [0,2]:");
    MAHI_write(segtree_sum(rt, 0, 2));
    MAHI_write("RangeTree min [0,2]:");
    MAHI_write(segtree_min(rt, 0, 2));

    // Matrix usage
    Matrix m = matrix_new(2, 2);
    matrix_set(m, 0, 0, 1.0);
    matrix_set(m, 0, 1, 2.0);
    matrix_set(m, 1, 0, 3.0);
    matrix_set(m, 1, 1, 4.0);
    MAHI_write("Matrix m[1][0]:");
    MAHI_write(matrix_get(m, 1, 0));

    Matrix id = matrix_identity(2);
    Matrix mm = matrix_mul(m, id);
    MAHI_write("Matrix mul by identity, mm[0][1]:");
    MAHI_write(matrix_get(mm, 0, 1));

    // Ordered set usage
    OrderedSet os = oset_new();
    oset_insert(os, 30);
    oset_insert(os, 10);
    oset_insert(os, 20);
    MAHI_write("OrderedSet 1st element (0-based):");
    MAHI_write(oset_nth(os, 1));
    MAHI_write("OrderedSet contains 20:");
    MAHI_write(oset_contains(os, 20));

    // Stack and Queue usage
    Stack st = stack_new();
    stack_push(st, 100);
    stack_push(st, 200);
    MAHI_write("Stack top:");
    MAHI_write(stack_top(st));
    MAHI_write("Stack size:");
    MAHI_write(stack_size(st));

    Queue q = queue_new();
    queue_push(q, 7);
    queue_push(q, 9);
    MAHI_write("Queue front:");
    MAHI_write(queue_front(q));
    MAHI_write("Queue size:");
    MAHI_write(queue_size(q));

    MAHI_write("=== Linear Pipeline Demo End ===");
}
