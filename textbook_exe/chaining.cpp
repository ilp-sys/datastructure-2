#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 7
#define SIZE 5

typedef struct element{
    int key;
}element;

void hash_chain_print(struct list *ht[]){
    struct list* node;
    printf("\n==============================\n");
    for(int i = 0; i < TABLE_SIZE; i++){
        printf("[%d]->", i);
    }
    printf("\n==============================\n");
}

int main(int argc, char* argv[]){

    int data[SIZE] = {8, 1, 9, 6, 13};
    element e;

    for(int i = 0l i < SIZE; i++){
        e.key = data[i];
        hash_chain_print(hash_table);
    }

    for(int i = 0; i < SIZE; i++){
        e.key = data[i];
        hash_chain_search(e, hash_table);
    }

    return 0;
}
