#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <memory.h>
using namespace std;
#define MAX_VERTICES 100

typedef struct GraphType{
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType *g){
    g->n = 0;
    memset(g, 0, sizeof(*g));
}

void insert_vertex(GraphType *g, int v){
    if((g->n)+1 > MAX_VERTICES){
        fprintf(stderr, "graph vertex num overflow!\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int u , int v){
    if(u >= g->n || v >= g->n){
        fprintf(stderr, "graph: vertex num err\n");
        return;
    }
    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1;
}

void del_edge(GraphType* g, int u ,int v){
    if(u >= g->n || v >= g->n){
        fprintf(stderr, "graph: vertex num err\n");
        return;
    }
    g->adj_mat[u][v] = 0;
    g->adj_mat[v][u] = 0;
}

int visited[MAX_VERTICES] = {0};
int bfs_bln(GraphType *g, int u, int v){
    queue<int> q;

    visited[u] = 1;
    q.push(u);
    while(!q.empty()){
         u = q.front(); q.pop();
         for(int w = 0; w < g->n; w++)
             if(g->adj_mat[u][w] && !visited[w]){
                 visited[w] = 1;
                 if(w == v) return 1;
                 q.push(w);
             }
    }
    return 0;
}

void dfs_print(GraphType* g, int u, int v){
    visited[u] = 1;
    printf("%d - ", u);
    for(int w = 0; w < g->n; w++){
        if(g->adj_mat[u][w] && !visited[w])
            dfs_print(g, w, v);
    }
}

void showMenu(){
    printf("1.add edge/ 2. del edge/ 3. find path/ 4. exit\n");
    printf(">>");
}

int main(int argc, char* argv[]){

    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g);
    for(int i = 0; i < 10; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 1, 3);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 6);
    insert_edge(g, 3, 8);
    insert_edge(g, 4, 5);
    insert_edge(g, 6, 7);
    insert_edge(g, 8, 9);

    int flag = 1;
    int menu = 0;

    while(flag){
        showMenu();
        scanf("%d", &menu);
        switch(menu){
            case 1:{
                       int count = 0;
                       int u = 0, v = 0;
                       while(1){
                           scanf("%d %d", &u, &v);
                           if(u == -1 && v == -1) break;
                           else{ 
                               insert_edge(g, u ,v);
                               count++;
                           }
                       }
                       printf("%d edges added!\n", count);
                       break;
                   }
            case 2:{
                       int count = 0;
                       int u = 0, v = 0;
                       while(1){
                           scanf("%d %d", &u, &v);
                           if(u == -1 && v == -1) break;
                           else{ 
                               del_edge(g, u ,v);
                               count++;
                           }
                       }
                       printf("%d edges deleted!\n", count);
                       break;
                   }
            case 3:{
                       int u = 0, v = 0;
                       scanf("%d %d", &u, &v);
                       int bln = bfs_bln(g, u, v);
                       memset(visited , 0, sizeof(visited));
                       if(bln){
                           printf("PATH 발견: ");
                            dfs_print(g, u, v);
                            memset(visited , 0, sizeof(visited));
                            printf("\n");
                       }
                       else printf("PAHT NOT EXIST\n");
                       break;
                   }
            case 4:
                flag = 0;
                printf("BYE\n");
                break;
        }
    }

    return 0;
}
