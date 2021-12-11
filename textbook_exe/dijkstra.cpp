#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType{
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES];//shortest path
int found[MAX_VERTICES]; //mark visited vertex

int choose(int distance[], int n, int found[]){
    int min = INT_MAX;
    int minpos = -1;
    for(int i = 0; i < n; i++)
        if(distance[i] < min && !found[i]){
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void print_status(GraphType *g){
    static int step = 1;
    printf("STEP %d: ", step++);
    printf("distance: ");
    for(int i = 0; i < g->n; i++){
        if(distance[i] == INF)
            printf(" * ");
        else
            printf("%3d", distance[i]);
    }
    printf("\nfound: ");
    for(int i = 0; i < g->n; i++)
        printf("%3d", found[i]);
    printf("\n\n");
}

void shortest_path(GraphType* g, int start){
    for(int i = 0; i < g->n; i++){ //initialize
        distance[i] = g->weight[start][i];
        found[i] = false;
    }
    found[start] = true;
    distance[start] = 0;
    for(int i = 0; i < g->n; i++){
        print_status(g);
        int u = choose(distance, g->n, found);
        found[u] = true;
        for(int w = 0; w < g->n; w++)
            if(!found[w])
                if(distance[u] + g->weight[u][w] < distance[w])
                    distance[w] = distance[u] + g->weight[u][w];
    }
}

int main(int argc, char* argv[]){
    GraphType g = { 7,
        {{0, 7, INF, INF, 3, 10, INF},
          {7, 0, 4, 10, 2, 6, INF},
          {INF, 4, 0, 2, INF, INF, INF},
          {INF, 10, 2, 0, 11, 9, 4},
          {3, 2, INF, 11, 0, INF, 5},
          {10, 6, INF, 9, INF, 0, INF},
          {INF, INF, INF, 4, 5, INF, 0}}
    };
    shortest_path(&g, 0);
    return 0;
}
