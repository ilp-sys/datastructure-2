#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <queue>
using namespace std;

#define MAX_VERTICES 100

typedef struct GraphType{
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES] = {false};

void init(GraphType* g){
    g->n = 0;
    memset(g, 0, sizeof(*g));
}

void insert_vertex(GraphType *g, int v){
    if((g->n)+1 > MAX_VERTICES){
        fprintf(stderr, "max vertex overflow\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int u, int v){
    if(u >= g->n || v >= g->n){
        fprintf(stderr, "Wrong vertex num!\n");
        return;
    }
    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1;
}

void bfs_mat(GraphType* g, int v){
    queue<int> q;
    visited[v] = true;
    printf("visit %d -> ", v);
    q.push(v);
    while(!q.empty()){
        v = q.front(); q.pop();
        for(int w = 0; w < g->n; w++){
            if(g->adj_mat[v][w] && !visited[w]){
                visited[w] = true;
                printf("visit %d -> ", w);
                q.push(w);
            }
        }
    }
}

int main(int argc, char* argv[]){

    GraphType *g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for(int i = 0; i < 6; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);
    
    printf("breadth first search!\n");
    bfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}
