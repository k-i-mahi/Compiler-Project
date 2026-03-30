/*
 * Runtime data structures for Linear language (graphs, trees, DSU, matrices, etc.)
 */

#ifndef DS_RUNTIME_H
#define DS_RUNTIME_H

#include <stddef.h>

typedef struct LinGraph LinGraph;
typedef struct LinTree LinTree;
typedef struct LinDSU LinDSU;
typedef struct LinMatrix LinMatrix;
typedef struct LinOSet LinOSet;
typedef struct LinSegTree LinSegTree;
typedef struct LinStack LinStack;
typedef struct LinQueue LinQueue;

/* --- Graph (undirected, vertices 0..n-1) --- */
LinGraph *lin_graph_new(int n);
void lin_graph_free(LinGraph *g); /* decrements ref; frees when 0 */
LinGraph *lin_graph_grab(LinGraph *g);
void lin_graph_add_edge(LinGraph *g, int u, int v);
int lin_graph_shortest_path(LinGraph *g, int s, int t); /* BFS; -1 if unreachable */
int lin_graph_connected(LinGraph *g, int s, int t);
int lin_graph_dfs_count(LinGraph *g, int start); /* nodes reached from start */

/* --- Rooted tree (0..n-1), parent[root] = -1 --- */
LinTree *lin_tree_new(int n);
void lin_tree_free(LinTree *t);
LinTree *lin_tree_grab(LinTree *t);
void lin_tree_set_parent(LinTree *t, int node, int parent);
int lin_tree_lca(LinTree *t, int a, int b);
int lin_tree_depth(LinTree *t, int v);

/* --- Disjoint Set Union --- */
LinDSU *lin_dsu_new(int n);
void lin_dsu_free(LinDSU *d);
LinDSU *lin_dsu_grab(LinDSU *d);
void lin_dsu_union(LinDSU *d, int a, int b);
int lin_dsu_find(LinDSU *d, int x);
int lin_dsu_same(LinDSU *d, int a, int b);

/* --- Matrix (real values) --- */
LinMatrix *lin_matrix_new(int rows, int cols);
void lin_matrix_free(LinMatrix *m);
LinMatrix *lin_matrix_grab(LinMatrix *m);
int lin_matrix_rows(LinMatrix *m);
int lin_matrix_cols(LinMatrix *m);
double lin_matrix_get(LinMatrix *m, int i, int j);
void lin_matrix_set(LinMatrix *m, int i, int j, double v);
LinMatrix *lin_matrix_add(LinMatrix *a, LinMatrix *b);
LinMatrix *lin_matrix_mul(LinMatrix *a, LinMatrix *b);
LinMatrix *lin_matrix_transpose(LinMatrix *m);
LinMatrix *lin_matrix_identity(int n);

/* --- Ordered set (sorted unique integers) --- */
LinOSet *lin_oset_new(void);
void lin_oset_free(LinOSet *s);
LinOSet *lin_oset_grab(LinOSet *s);
void lin_oset_insert(LinOSet *s, int x);
void lin_oset_erase(LinOSet *s, int x);
int lin_oset_size(LinOSet *s);
int lin_oset_contains(LinOSet *s, int x);
int lin_oset_nth(LinOSet *s, int k); /* k-th smallest, 0-based; -1 if invalid */

/* --- Range / segment tree (point assign, range sum & min on ints) --- */
LinSegTree *lin_segtree_new(int n);
void lin_segtree_free(LinSegTree *st);
LinSegTree *lin_segtree_grab(LinSegTree *st);
void lin_segtree_set(LinSegTree *st, int i, int val);
int lin_segtree_sum(LinSegTree *st, int l, int r); /* inclusive */
int lin_segtree_min(LinSegTree *st, int l, int r);

/* --- Stack (integers) --- */
LinStack *lin_stack_new(void);
void lin_stack_free(LinStack *s);
LinStack *lin_stack_grab(LinStack *s);
void lin_stack_push(LinStack *s, int x);
int lin_stack_pop(LinStack *s);
int lin_stack_top(LinStack *s);
int lin_stack_empty(LinStack *s);
int lin_stack_size(LinStack *s);

/* --- Queue (integers) --- */
LinQueue *lin_queue_new(void);
void lin_queue_free(LinQueue *q);
LinQueue *lin_queue_grab(LinQueue *q);
void lin_queue_push(LinQueue *q, int x);
int lin_queue_pop(LinQueue *q);
int lin_queue_front(LinQueue *q);
int lin_queue_empty(LinQueue *q);
int lin_queue_size(LinQueue *q);

#endif
