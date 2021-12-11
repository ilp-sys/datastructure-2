#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>

#define INFINITE 199990
#define MAX_VERTICES 20001

typedef struct GraphNode{
    int vertex;
    int weight;
    GraphNode* link;
}GraphNode;

typedef struct GraphType{
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}Graphtype;

void init(GraphType *g){
    g->n = 0;
    memset(g->adj_list, (int)NULL, sizeof(g->adj_list));
}

void insertEdge(GraphType* g, int u, int v, int w){//방향그래프 -> 입력받은 방향으로만 연결
    GraphNode* new_node = (GraphNode*)malloc(sizeof(GraphNode));
    new_node->vertex = v; 
    new_node->weight = w;
    new_node->link = g->adj_list[u];
    g->adj_list[u] = new_node;
}

int distance[MAX_VERTICES]; //shortest path from specific node
int visited[MAX_VERTICES];//mark visited

int findSmallest(int vertex_num){
    :q

}

void dijkstra(GraphType *g, int start_vertex){

    //initialize
    for(int i = 0; i < MAX_VERTICES; i++){
        distance[i] = INFINITE;
        visited[i] = false;
    }

    //beginning step
    visited[start_vertex] = true;
    distance[start_vertex] = 0;
    for(GraphNode* tmp = g->adj_list[start_vertex]; tmp; tmp = tmp->link)
        distance[tmp->vertex] = tmp->weight;

    //iterate
    for(int i = 0; i < g->n -1; i++){
        int smallest = findSmallest(g->n); //find smallest path
        if(smallest == 0) break;
        visited[smallest] = true; //mark as visited
        for(GraphNode* tmp = g->adj_list[smallest]; tmp; tmp = tmp->link)
            if(!visited[tmp->vertex]) //update distance table
                if(distance[smallest] + tmp->weight < distance[tmp->vertex])
                    distance[tmp->vertex] = distance[smallest] + tmp->weight; 
    }
}

int main(int argc, char* argv[]){

    //declare & initialize graph
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    //get input
    int vertex_num = 0, edge_num = 0;
    scanf("%d %d", &vertex_num, &edge_num);
    g->n = vertex_num;

    int start_vertex = 0;
    scanf("%d", &start_vertex);

    for(int i = 0; i < edge_num; i++){
        int u = 0, v = 0, w = 0;
        scanf("%d %d %d", &u, &v, &w);
        insertEdge(g, u, v, w);
    }

    //find shortest path
    dijkstra(g, start_vertex);

    //print shortest path
    for(int i = 1; i < g->n+1; i++){
        if(distance[i] == INFINITE) printf("INF\n");
        else printf("%d\n", distance[i]);
    }

    free(g);
    return 0;
}
