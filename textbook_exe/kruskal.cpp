#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];//부모 포인터 표현, reperesent union-find set
void set_init(int n){
    memset(parent, -1, sizeof(parent));
}

int set_find(int curr){
    if(parent[curr] == -1)
        return curr;
    while(parent[curr] != -1) 
        curr = parent[curr];
    return curr;
}

int set_union(int a, int b){
    int root1 = set_find(a);
    int root2 = set_find(b);
    if(root1 != root2)
        parent[root1] = root2;
}

typedef struct Egde{
    int u, v, w;
}Edge;

typedef struct GraphType{
    int n; //number of edges
    Egde edges[2*MAX_VERTICES];
}GraphType;

void graph_init(GraphType *g){
    g->n = 0;
    for(int i = 0; i < 2*MAX_VERTICES; i++){
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

int compare(const void* a, const void* b){
    Egde* x = (Edge*)a;
    Egde* y = (Edge*)b;
    return (x->w - y->w);
}

void kruskal(GraphType *g){
    int edge_accepted = 0; //number of edges selected

    set_init(g->n);//부모포인터 집합 초기화
          //정렬할 배열, 배열의 원소 수, 원소 하나의 크기, 비교를 수행할 함수 포인터                                     
    qsort(g->edges, g->n, sizeof(Edge), compare);//edge를 가중치 순으로 정렬

    printf("Kruskal minimum spanning tree\n");
    int i = 0;
    while(edge_accepted < (g->n -1)){//간선 = 모든 노드의 수 -1
        Edge e = g->edges[i];
        int uset = set_find(e.u);//vertex u set number
        int vset = set_find(e.v);//vertex v set number
        if(uset != vset){
            printf("edge(%d, %d) %d selected\n", e.u, e.v, e.w);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

int main(int argc, char* argv[]){
    GraphType *g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);
    return 0;
}
//간선 = 모든 노드의 수 -1
