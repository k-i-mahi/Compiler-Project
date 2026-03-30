/*
 * Runtime data structures for Linear language
 */

#include "ds_runtime.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* ========== Graph ========== */
struct LinGraph {
    int ref;
    int n;
    int **adj;
    int *deg;
    int *cap;
};

static void graph_ensure(LinGraph *g, int u) {
    if (g->deg[u] >= g->cap[u]) {
        int nc = g->cap[u] ? g->cap[u] * 2 : 4;
        g->adj[u] = (int *)realloc(g->adj[u], (size_t)nc * sizeof(int));
        g->cap[u] = nc;
    }
}

LinGraph *lin_graph_new(int n) {
    if (n < 0) n = 0;
    LinGraph *g = (LinGraph *)calloc(1, sizeof(LinGraph));
    if (!g) return NULL;
    g->ref = 1;
    g->n = n;
    if (n > 0) {
        g->adj = (int **)calloc((size_t)n, sizeof(int *));
        g->deg = (int *)calloc((size_t)n, sizeof(int));
        g->cap = (int *)calloc((size_t)n, sizeof(int));
        if (!g->adj || !g->deg || !g->cap) {
            lin_graph_free(g);
            return NULL;
        }
    }
    return g;
}

LinGraph *lin_graph_grab(LinGraph *g) {
    if (g) g->ref++;
    return g;
}

void lin_graph_free(LinGraph *g) {
    if (!g) return;
    if (--g->ref > 0) return;
    for (int i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g->deg);
    free(g->cap);
    free(g);
}

void lin_graph_add_edge(LinGraph *g, int u, int v) {
    if (!g || u < 0 || v < 0 || u >= g->n || v >= g->n || u == v) return;
    graph_ensure(g, u);
    graph_ensure(g, v);
    g->adj[u][g->deg[u]++] = v;
    g->adj[v][g->deg[v]++] = u;
}

int lin_graph_shortest_path(LinGraph *g, int s, int t) {
    if (!g || s < 0 || t < 0 || s >= g->n || t >= g->n) return -1;
    if (s == t) return 0;
    int *dist = (int *)malloc((size_t)g->n * sizeof(int));
    int *q = (int *)malloc((size_t)g->n * sizeof(int));
    if (!dist || !q) {
        free(dist);
        free(q);
        return -1;
    }
    for (int i = 0; i < g->n; i++) dist[i] = -1;
    int qh = 0, qt = 0;
    dist[s] = 0;
    q[qt++] = s;
    while (qh < qt) {
        int u = q[qh++];
        if (u == t) {
            int d = dist[t];
            free(dist);
            free(q);
            return d;
        }
        for (int k = 0; k < g->deg[u]; k++) {
            int v = g->adj[u][k];
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                q[qt++] = v;
            }
        }
    }
    free(dist);
    free(q);
    return -1;
}

int lin_graph_connected(LinGraph *g, int s, int t) {
    return lin_graph_shortest_path(g, s, t) >= 0 ? 1 : 0;
}

static void dfs_vis(LinGraph *g, int u, int *vis) {
    vis[u] = 1;
    for (int k = 0; k < g->deg[u]; k++) {
        int v = g->adj[u][k];
        if (!vis[v]) dfs_vis(g, v, vis);
    }
}

int lin_graph_dfs_count(LinGraph *g, int start) {
    if (!g || start < 0 || start >= g->n) return 0;
    int *vis = (int *)calloc((size_t)g->n, sizeof(int));
    if (!vis) return 0;
    dfs_vis(g, start, vis);
    int c = 0;
    for (int i = 0; i < g->n; i++)
        if (vis[i]) c++;
    free(vis);
    return c;
}

/* ========== Tree ========== */
struct LinTree {
    int ref;
    int n;
    int *parent;
};

LinTree *lin_tree_new(int n) {
    if (n < 0) n = 0;
    LinTree *t = (LinTree *)calloc(1, sizeof(LinTree));
    if (!t) return NULL;
    t->ref = 1;
    t->n = n;
    if (n > 0) {
        t->parent = (int *)malloc((size_t)n * sizeof(int));
        if (!t->parent) {
            free(t);
            return NULL;
        }
        for (int i = 0; i < n; i++) t->parent[i] = -1;
    }
    return t;
}

LinTree *lin_tree_grab(LinTree *t) {
    if (t) t->ref++;
    return t;
}

void lin_tree_free(LinTree *t) {
    if (!t) return;
    if (--t->ref > 0) return;
    free(t->parent);
    free(t);
}

void lin_tree_set_parent(LinTree *t, int node, int parent) {
    if (!t || node < 0 || node >= t->n) return;
    t->parent[node] = parent;
}

static int tree_lift(LinTree *t, int v, int steps) {
    while (steps-- > 0 && v >= 0) v = t->parent[v];
    return v;
}

int lin_tree_depth(LinTree *t, int v) {
    if (!t || v < 0 || v >= t->n) return 0;
    int d = 0;
    while (v >= 0 && t->parent[v] >= 0) {
        d++;
        v = t->parent[v];
    }
    return d;
}

int lin_tree_lca(LinTree *t, int a, int b) {
    if (!t || a < 0 || b < 0 || a >= t->n || b >= t->n) return -1;
    if (a == b) return a;
    int da = lin_tree_depth(t, a);
    int db = lin_tree_depth(t, b);
    if (da < db) {
        b = tree_lift(t, b, db - da);
    } else if (db < da) {
        a = tree_lift(t, a, da - db);
    }
    while (a != b && a >= 0 && b >= 0) {
        a = t->parent[a];
        b = t->parent[b];
    }
    return (a == b) ? a : -1;
}

/* ========== DSU ========== */
struct LinDSU {
    int ref;
    int n;
    int *parent;
    int *rank;
};

LinDSU *lin_dsu_new(int n) {
    if (n < 0) n = 0;
    LinDSU *d = (LinDSU *)calloc(1, sizeof(LinDSU));
    if (!d) return NULL;
    d->ref = 1;
    d->n = n;
    if (n > 0) {
        d->parent = (int *)malloc((size_t)n * sizeof(int));
        d->rank = (int *)calloc((size_t)n, sizeof(int));
        if (!d->parent || !d->rank) {
            lin_dsu_free(d);
            return NULL;
        }
        for (int i = 0; i < n; i++) d->parent[i] = i;
    }
    return d;
}

LinDSU *lin_dsu_grab(LinDSU *d) {
    if (d) d->ref++;
    return d;
}

void lin_dsu_free(LinDSU *d) {
    if (!d) return;
    if (--d->ref > 0) return;
    free(d->parent);
    free(d->rank);
    free(d);
}

int lin_dsu_find(LinDSU *d, int x) {
    if (!d || x < 0 || x >= d->n) return -1;
    if (d->parent[x] != x) d->parent[x] = lin_dsu_find(d, d->parent[x]);
    return d->parent[x];
}

void lin_dsu_union(LinDSU *d, int a, int b) {
    if (!d) return;
    a = lin_dsu_find(d, a);
    b = lin_dsu_find(d, b);
    if (a < 0 || b < 0 || a == b) return;
    if (d->rank[a] < d->rank[b]) {
        int t = a;
        a = b;
        b = t;
    }
    d->parent[b] = a;
    if (d->rank[a] == d->rank[b]) d->rank[a]++;
}

int lin_dsu_same(LinDSU *d, int a, int b) {
    return lin_dsu_find(d, a) == lin_dsu_find(d, b) ? 1 : 0;
}

/* ========== Matrix ========== */
struct LinMatrix {
    int ref;
    int rows, cols;
    double *data;
};

LinMatrix *lin_matrix_new(int rows, int cols) {
    if (rows < 0) rows = 0;
    if (cols < 0) cols = 0;
    LinMatrix *m = (LinMatrix *)calloc(1, sizeof(LinMatrix));
    if (!m) return NULL;
    m->ref = 1;
    m->rows = rows;
    m->cols = cols;
    if (rows > 0 && cols > 0) {
        m->data = (double *)calloc((size_t)rows * (size_t)cols, sizeof(double));
        if (!m->data) {
            free(m);
            return NULL;
        }
    }
    return m;
}

LinMatrix *lin_matrix_grab(LinMatrix *m) {
    if (m) m->ref++;
    return m;
}

void lin_matrix_free(LinMatrix *m) {
    if (!m) return;
    if (--m->ref > 0) return;
    free(m->data);
    free(m);
}

int lin_matrix_rows(LinMatrix *m) { return m ? m->rows : 0; }
int lin_matrix_cols(LinMatrix *m) { return m ? m->cols : 0; }

double lin_matrix_get(LinMatrix *m, int i, int j) {
    if (!m || i < 0 || j < 0 || i >= m->rows || j >= m->cols) return 0.0;
    return m->data[i * m->cols + j];
}

void lin_matrix_set(LinMatrix *m, int i, int j, double v) {
    if (!m || i < 0 || j < 0 || i >= m->rows || j >= m->cols) return;
    m->data[i * m->cols + j] = v;
}

LinMatrix *lin_matrix_add(LinMatrix *a, LinMatrix *b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols) return NULL;
    LinMatrix *c = lin_matrix_new(a->rows, a->cols);
    if (!c) return NULL;
    for (int i = 0; i < a->rows * a->cols; i++)
        c->data[i] = a->data[i] + b->data[i];
    return c;
}

LinMatrix *lin_matrix_mul(LinMatrix *a, LinMatrix *b) {
    if (!a || !b || a->cols != b->rows) return NULL;
    LinMatrix *c = lin_matrix_new(a->rows, b->cols);
    if (!c) return NULL;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            double s = 0;
            for (int k = 0; k < a->cols; k++)
                s += lin_matrix_get(a, i, k) * lin_matrix_get(b, k, j);
            lin_matrix_set(c, i, j, s);
        }
    }
    return c;
}

LinMatrix *lin_matrix_transpose(LinMatrix *m) {
    if (!m) return NULL;
    LinMatrix *t = lin_matrix_new(m->cols, m->rows);
    if (!t) return NULL;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->cols; j++)
            lin_matrix_set(t, j, i, lin_matrix_get(m, i, j));
    return t;
}

LinMatrix *lin_matrix_identity(int n) {
    LinMatrix *m = lin_matrix_new(n, n);
    if (!m) return NULL;
    for (int i = 0; i < n; i++) lin_matrix_set(m, i, i, 1.0);
    return m;
}

/* ========== Ordered set (sorted unique ints) ========== */
struct LinOSet {
    int ref;
    int *a;
    int n, cap;
};

LinOSet *lin_oset_new(void) {
    LinOSet *s = (LinOSet *)calloc(1, sizeof(LinOSet));
    if (s) s->ref = 1;
    return s;
}

LinOSet *lin_oset_grab(LinOSet *s) {
    if (s) s->ref++;
    return s;
}

void lin_oset_free(LinOSet *s) {
    if (!s) return;
    if (--s->ref > 0) return;
    free(s->a);
    free(s);
}

static int oset_find_idx(LinOSet *s, int x) {
    int lo = 0, hi = s->n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (s->a[mid] == x) return mid;
        if (s->a[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1 - lo;
}

void lin_oset_insert(LinOSet *s, int x) {
    if (!s) return;
    int idx = oset_find_idx(s, x);
    if (idx >= 0) return;
    int ins = -idx - 1;
    if (s->n >= s->cap) {
        int nc = s->cap ? s->cap * 2 : 8;
        s->a = (int *)realloc(s->a, (size_t)nc * sizeof(int));
        s->cap = nc;
    }
    memmove(s->a + ins + 1, s->a + ins, (size_t)(s->n - ins) * sizeof(int));
    s->a[ins] = x;
    s->n++;
}

void lin_oset_erase(LinOSet *s, int x) {
    if (!s) return;
    int idx = oset_find_idx(s, x);
    if (idx < 0) return;
    memmove(s->a + idx, s->a + idx + 1, (size_t)(s->n - idx - 1) * sizeof(int));
    s->n--;
}

int lin_oset_size(LinOSet *s) { return s ? s->n : 0; }

int lin_oset_contains(LinOSet *s, int x) {
    if (!s) return 0;
    return oset_find_idx(s, x) >= 0 ? 1 : 0;
}

int lin_oset_nth(LinOSet *s, int k) {
    if (!s || k < 0 || k >= s->n) return -1;
    return s->a[k];
}

/* ========== Segment tree ========== */
struct LinSegTree {
    int ref;
    int n;
    int *sumt;
    int *mint;
    int cap;
};

static void st_build(LinSegTree *st, int idx, int l, int r) {
    if (l == r) {
        st->sumt[idx] = 0;
        st->mint[idx] = 0;
        return;
    }
    int m = (l + r) / 2;
    st_build(st, idx * 2, l, m);
    st_build(st, idx * 2 + 1, m + 1, r);
    st->sumt[idx] = st->sumt[idx * 2] + st->sumt[idx * 2 + 1];
    int ml = st->mint[idx * 2], mr = st->mint[idx * 2 + 1];
    st->mint[idx] = ml < mr ? ml : mr;
}

LinSegTree *lin_segtree_new(int n) {
    if (n <= 0) n = 1;
    LinSegTree *st = (LinSegTree *)calloc(1, sizeof(LinSegTree));
    if (!st) return NULL;
    st->ref = 1;
    st->n = n;
    st->cap = 4 * n + 8;
    st->sumt = (int *)calloc((size_t)st->cap, sizeof(int));
    st->mint = (int *)malloc((size_t)st->cap * sizeof(int));
    if (!st->sumt || !st->mint) {
        lin_segtree_free(st);
        return NULL;
    }
    st_build(st, 1, 0, n - 1);
    return st;
}

LinSegTree *lin_segtree_grab(LinSegTree *st) {
    if (st) st->ref++;
    return st;
}

void lin_segtree_free(LinSegTree *st) {
    if (!st) return;
    if (--st->ref > 0) return;
    free(st->sumt);
    free(st->mint);
    free(st);
}

static void st_set(LinSegTree *st, int idx, int l, int r, int pos, int val) {
    if (l == r) {
        st->sumt[idx] = val;
        st->mint[idx] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m) st_set(st, idx * 2, l, m, pos, val);
    else st_set(st, idx * 2 + 1, m + 1, r, pos, val);
    st->sumt[idx] = st->sumt[idx * 2] + st->sumt[idx * 2 + 1];
    int ml = st->mint[idx * 2], mr = st->mint[idx * 2 + 1];
    st->mint[idx] = ml < mr ? ml : mr;
}

void lin_segtree_set(LinSegTree *st, int i, int val) {
    if (!st || i < 0 || i >= st->n) return;
    st_set(st, 1, 0, st->n - 1, i, val);
}

static int st_sum(LinSegTree *st, int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return st->sumt[idx];
    int m = (l + r) / 2;
    return st_sum(st, idx * 2, l, m, ql, qr) + st_sum(st, idx * 2 + 1, m + 1, r, ql, qr);
}

int lin_segtree_sum(LinSegTree *st, int l, int r) {
    if (!st || l > r || l < 0 || r >= st->n) return 0;
    return st_sum(st, 1, 0, st->n - 1, l, r);
}

static int st_min(LinSegTree *st, int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return INT_MAX;
    if (ql <= l && r <= qr) return st->mint[idx];
    int m = (l + r) / 2;
    int a = st_min(st, idx * 2, l, m, ql, qr);
    int b = st_min(st, idx * 2 + 1, m + 1, r, ql, qr);
    return a < b ? a : b;
}

int lin_segtree_min(LinSegTree *st, int l, int r) {
    if (!st || l > r || l < 0 || r >= st->n) return INT_MAX;
    return st_min(st, 1, 0, st->n - 1, l, r);
}

/* ========================================================================= */
/*                              STACK                                        */
/* ========================================================================= */

struct LinStack {
    int ref_count;
    int *data;
    int capacity;
    int size;
};

LinStack *lin_stack_new(void) {
    LinStack *s = (LinStack *)malloc(sizeof(LinStack));
    s->ref_count = 1;
    s->capacity = 16;
    s->size = 0;
    s->data = (int *)malloc(s->capacity * sizeof(int));
    return s;
}

void lin_stack_free(LinStack *s) {
    if (!s) return;
    s->ref_count--;
    if (s->ref_count <= 0) {
        free(s->data);
        free(s);
    }
}

LinStack *lin_stack_grab(LinStack *s) {
    if (s) s->ref_count++;
    return s;
}

void lin_stack_push(LinStack *s, int x) {
    if (!s) return;
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        s->data = (int *)realloc(s->data, s->capacity * sizeof(int));
    }
    s->data[s->size++] = x;
}

int lin_stack_pop(LinStack *s) {
    if (!s || s->size == 0) return 0;
    return s->data[--s->size];
}

int lin_stack_top(LinStack *s) {
    if (!s || s->size == 0) return 0;
    return s->data[s->size - 1];
}

int lin_stack_empty(LinStack *s) {
    return (!s || s->size == 0) ? 1 : 0;
}

int lin_stack_size(LinStack *s) {
    return s ? s->size : 0;
}

/* ========================================================================= */
/*                              QUEUE                                        */
/* ========================================================================= */

struct LinQueue {
    int ref_count;
    int *data;
    int capacity;
    int head;
    int tail;
    int size;
};

LinQueue *lin_queue_new(void) {
    LinQueue *q = (LinQueue *)malloc(sizeof(LinQueue));
    q->ref_count = 1;
    q->capacity = 16;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->data = (int *)malloc(q->capacity * sizeof(int));
    return q;
}

void lin_queue_free(LinQueue *q) {
    if (!q) return;
    q->ref_count--;
    if (q->ref_count <= 0) {
        free(q->data);
        free(q);
    }
}

LinQueue *lin_queue_grab(LinQueue *q) {
    if (q) q->ref_count++;
    return q;
}

void lin_queue_push(LinQueue *q, int x) {
    if (!q) return;
    if (q->size >= q->capacity) {
        int new_cap = q->capacity * 2;
        int *new_data = (int *)malloc(new_cap * sizeof(int));
        for (int i = 0; i < q->size; i++) {
            new_data[i] = q->data[(q->head + i) % q->capacity];
        }
        free(q->data);
        q->data = new_data;
        q->head = 0;
        q->tail = q->size;
        q->capacity = new_cap;
    }
    q->data[q->tail] = x;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
}

int lin_queue_pop(LinQueue *q) {
    if (!q || q->size == 0) return 0;
    int val = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return val;
}

int lin_queue_front(LinQueue *q) {
    if (!q || q->size == 0) return 0;
    return q->data[q->head];
}

int lin_queue_empty(LinQueue *q) {
    return (!q || q->size == 0) ? 1 : 0;
}

int lin_queue_size(LinQueue *q) {
    return q ? q->size : 0;
}
