#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_VERTICES 50

typedef struct GraphType{
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;


void init(GraphType* g){
    g->n = 0;
    memset(g, 0, sizeof(*g));
}

void insert_vertex(GraphType* g, int v){
    if((g->n) + 1 > MAX_VERTICES){
        fprintf(stderr, "Max vertices overflow!\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType *g, int u, int v){
    if(u >= g->n || v >= g->n){
        fprintf(stderr, "Graph: vertex num err\n");
        return;
    }

    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1;
}

int visited[MAX_VERTICES] = {false};
void dfs_mat(GraphType*g, int v){
    visited[v] = true;
    printf("vertex %d ->", v);
    for(int w = 0; w < g->n; w++){
        if(g->adj_mat[v][w] & !visited[w])
            dfs_mat(g, w);
    }
}

int main(int argc, char* argv[]){

    GraphType *g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for(int i = 0; i < 4; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    printf("depth first search!\n");
    dfs_mat(g, 0);
    printf("\n");
    free(g);

    return 0;
}
