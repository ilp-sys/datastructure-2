#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKET_SIZE 5
#define MAX_INPUT_SIZE 100

typedef struct slot{
    char word[MAX_INPUT_SIZE];
}slot;

typedef struct bucket{
    slot s;
    bucket* link;
}bucket;

bucket *hash_table[BUCKET_SIZE];

int hashFunction(char c){
    int hash_val = c % BUCKET_SIZE;
    return hash_val;
}

void addHashChain(slot s, bucket *hash_table[]){
    int hash_val = hashFunction(s.word[0]);

    bucket* ptr = (bucket*)malloc(sizeof(bucket));
    strcpy(ptr->s.word, s.word);
    ptr->link = NULL;

    bucket* node_before = NULL;
    for(bucket* node = hash_table[hash_val]; node; node_before = node, node = node->link);

    if(node_before){
        printf("(Collision!)\n");
        node_before->link = ptr;
    }
    else hash_table[hash_val] = ptr;
}

void printHashTable(bucket* hash_table[]){
    for(int i = 0; i < BUCKET_SIZE; i++){
        printf("%d: ", i);
        for(bucket* tmp = hash_table[i]; tmp; tmp = tmp->link)
            printf("- %s", tmp->s.word);
        printf("\n");
    }
    printf("- - - - - - - -\n");
}

void FunHashingQuiz(){
    char input[MAX_INPUT_SIZE];
    while(true){
        printf("INPUT>> ");
        scanf("%s", input);
        if(!strcmp(input, "exit"))
            break;
        slot s;
        strcpy(s.word, input);
        addHashChain(s, hash_table);
        printHashTable(hash_table);
    }
}

int main(int argc, char* argv[]){
    FunHashingQuiz();
    return 0;
}

