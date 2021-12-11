#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_VERTICES 10001
#define MAX_EDGES 100001
#define INF 1000001

typedef struct Edge{
    int u, v, w;
}Edge;

typedef struct GraphType{
    int n;
    Edge edges[MAX_EDGES];
}GraphType;

void graph_init(GraphType* g){
    g->n = 0;
    for(int i = 0; i < 2 * MAX_VERTICES; i++){
        g->edges[i].u = 0;
        g->edges[i].v = 0;
        g->edges[i].w = INF;
    }
}

void insert_edge(GraphType *g, int u, int v, int w){
    g->edges[g->n].u = u;
    g->edges[g->n].v = v;
    g->edges[g->n].w = w;
    g->n++;
}

int parent[MAX_VERTICES];

void set_init(int n){
    for(int i = 1; i < n+1; i++)
        parent[i] = -1;
}

int set_find(int curr){
    if(parent[curr] == -1) return curr;
    while(parent[curr] != -1) curr = parent[curr];
    return curr;
}

int compare(const void* a, const void* b){
    Edge* x = (Edge*) a;
    Edge* y = (Edge*) b;
    return (x->w - y->w);
}

void set_union(int a, int b){
    int root1 = set_find(a);
    int root2 = set_find(b);
    if(root1 != root2)
        parent[root1] = root2;
}

int kruskal(GraphType* g){
    int sum = 0, edge_accepted = 0;
    set_init(g->n);
    qsort(g->edges, g->n, sizeof(Edge), compare);

    int i = 0;
    while(edge_accepted < (g->n)-1){
        Edge e = g->edges[i];
        int uset = set_find(e.u);
        int vset = set_find(e.v);
        if(uset != vset){
            edge_accepted++;
            sum += e.w;
            set_union(uset, vset);
        }
        i++;
    }
    return sum;
}

int main(int argc, char* argv[]){

    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    int vertex_num = 0, edge_num = 0;
    scanf("%d %d", &vertex_num, &edge_num);

    for(int i = 0; i < edge_num; i++){
        int u = 0, v = 0, w = 0;
        scanf("%d %d %d", &u, &v,&w);
        insert_edge(g, u, v, w);
    }

    int sum = kruskal(g);
    printf("%d", sum);

    free(g);
    return 0;
}

