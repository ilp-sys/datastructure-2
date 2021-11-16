#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50

typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct GraphType{
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType* g){
    g->n = 0;
    for(int v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v){
    if((g->n)+1 > MAX_VERTICES){
        fprintf(stderr, "vertex num overflow\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int u, int v){
   if(u >= g->n || v >= g->n) {
       fprintf(stderr, "wrong vertex num!\n");
       return;
   }
   GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
   node->vertex = v;
   node->link = g->adj_list[u];//???? 납득할 수 없어요 -> 납득 완
   g->adj_list[u] = node;
}

void print_adj_list(GraphType* g){
    for(int i = 0; i < g->n; i++){
        GraphNode* p = g->adj_list[i];
        printf("vertex %d's linked list: ", i);
        while(p != NULL){
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

int visited[MAX_VERTICES] = {false};
void dfs_list(GraphType* g, int v){
    visited[v] = true;
    printf("vertex %d -> ", v);
    for(GraphNode* w = g->adj_list[v]; w; w = w->link){
        if(!visited[w->vertex])
            dfs_list(g, w->vertex);
    }
}

int main(int argc, char* argv[]){
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for(int i = 0; i < 4; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);

    print_adj_list(g);

    printf("depth first search!\n");
    dfs_list(g, 0);

    return 0;
}
