#include <stdio.h>
#include <stdlib.h>
#define MAX_N 20

int vis[MAX_N];

typedef enum { DG, UDG, DN, UDN } GType;

typedef struct Arc {
    int to;
    struct Arc* next;
} Arc;

typedef struct {
    int val;
    Arc* head;
} Vertex;

typedef struct {
    Vertex v[MAX_N];
    int vn, an;
    GType type;
} Graph;

typedef struct {
    int q[MAX_N];
    int head, tail, size;
} Queue;

int find(Graph g, int x);
void create(Graph* g, int n, int m);
void init_q(Queue* q);
void push(Queue* q, int x);
void pop(Queue* q, int* x);
int bfs(Graph g, int s, int t);

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    Graph g;
    create(&g, n, m);
    for (int i = 0; i < g.vn; i++) vis[i] = 0;
    int a, b;
    scanf("%d%d", &a, &b);
    printf(bfs(g, find(g, a), find(g, b)) ? "yes" : "no");
    return 0;
}

int find(Graph g, int x) {
    for (int i = 0; i < g.vn; i++)
        if (g.v[i].val == x) return i;
    return -1;
}

void create(Graph* g, int n, int m) {
    g->vn = n;
    g->an = m;
    g->type = DG;
    for (int i = 0; i < n; i++) {
        scanf("%d", &g->v[i].val);
        g->v[i].head = NULL;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        Arc* a = (Arc*)malloc(sizeof(Arc));
        a->to = v;
        int p = find(*g, u);
        a->next = g->v[p].head;
        g->v[p].head = a;
    }
}

void init_q(Queue* q) {
    q->head = 0;
    q->tail = -1;
    q->size = 0;
}

void push(Queue* q, int x) {
    if (q->size >= MAX_N) return;
    q->tail = (q->tail + 1) % MAX_N;
    q->q[q->tail] = x;
    q->size++;
}

void pop(Queue* q, int* x) {
    if (q->size == 0) return;
    *x = q->q[q->head];
    q->head = (q->head + 1) % MAX_N;
    q->size--;
}

int bfs(Graph g, int s, int t) {
    Queue q;
    init_q(&q);
    vis[s] = 1;
    push(&q, s);
    if (s == t) return 1;
    while (q.size) {
        int u;
        pop(&q, &u);
        for (Arc* a = g.v[u].head; a; a = a->next) {
            int v = find(g, a->to);
            if (!vis[v]) {
                if (v == t) return 1;
                vis[v] = 1;
                push(&q, v);
            }
        }
    }
    return 0;
}