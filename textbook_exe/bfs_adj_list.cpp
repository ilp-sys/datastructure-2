#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;
#define MAX_VERTICES 100

typedef struct GraphNode{
    int vertex;
    GraphNode* link;
}GraphNode;

typedef struct GraphType{
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType *g){
    g->n = 0;
    for(int v = 0; v < MAX_VERTICESl; v++)
        g->adj_list[v] = NULL;
}

int visited[MAX_VERTICES];

void insert_vertex(GraphType* g, int v){
    if((g->n)+1 > MAX_VERTICES){
        fprintf(stderr, "vertex num overflow\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType *g, int u, int v){
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

int main(int argc, char* argv[]){
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for(int i = 0; i < 6; i++)
        insert_node(g, i);

    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("breadth first search!\n");
    bfs_list(g, 0);
    printf("\n");
    free(g);

    return 0;
a
