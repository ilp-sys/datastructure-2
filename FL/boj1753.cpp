#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#define MAX_VERTICES 20000
#define INF 11

typedef struct GraphType{
    int n; //정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int set_s[MAX_VERTICES];
int distance[MAX_VERTICES];

int getNearestVertex(int vertex_num){
    int min = INT_MAX;
    int minpos = -1;
    for(int i =0; i < vertex_num; i++)
        if(distance[i] < min && !set_s[i]){
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

/*
void printStatus(GraphType* g){
    static int step = 1;
    printf("STEP %d>>\n", step++);
    printf("distance: ");
    for(int i = 0; i < g->n; i++){
        if(distance[i] == INF)
            printf(" INF ");
        else printf("%4d" , distance[i]);
    }
    printf("\nset_s: ");
    for(int i = 0; i < g->n; i++)
        printf("%4d", set_s[i]);
    printf("\n\n");
}
*/

void shortestPath(GraphType* g, int start_vertex){
    for(int i = 0; i < g->n; i++){ //initialize distace and set_s array for first iter
        distance[i] = g->weight[start_vertex][i];
        set_s[i] = false;
    }

    set_s[start_vertex] = true; //just visited start_vertex!
    distance[start_vertex] = 0;

    for(int i = 0; i < g->n-1; i++){
        //printStatus(g);;
        int nv = getNearestVertex(g->n); //get a adjacent vertex with cheapest weight
        set_s[nv] = true; //update set_s
        for(int j = 0; j < g->n; j++) //update distance
            if(!set_s[j])
                if(distance[nv] + g->weight[nv][j] < distance[j])
                    distance[j] = distance[nv] + g->weight[nv][j];
    }
}

int main(int argc, char* argv[]){

    //get input
    int vertex_num = 0, edge_num = 0;
    scanf("%d %d", &vertex_num, &edge_num);

    int start_vertex= 0;
    scanf("%d", &start_vertex);
    start_vertex--;

    //initialize GraphType
    static GraphType g;
    g.n = vertex_num;
    memset(g.weight, INF, sizeof(g.weight));

    for(int i = 0; i < edge_num; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;
        g.weight[u][v] = w; 
        //g.weight[v][u] = w; //무방향 그래프
    }

    shortestPath(&g, start_vertex);

    for(int i = 0; i < g.n; i++){
        if(distance[i] >=  INF)
            printf("INF\n");
        else
            printf("%d\n", distance[i]);
    }

    return 0;
}
