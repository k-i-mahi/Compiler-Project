/* Auto-generated C file from Linear source: .\samples\sample_ast.linear */
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
    // Declarations
    int x = 10;
    float y = 3.14;
    char* msg = "Hello from Linear!";

    // Arithmetic and Control Flow
    x = x + 5 * 2;

    if (x > 15) {
        MAHI_write(msg);
    } else {
        int z = 0;
        while (z < 5) {
            z = z + 1;
        }
    }
}
