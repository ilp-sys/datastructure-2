#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 100

typedef struct{
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
}element;

typedef struct node{
    element e;
    node *left, *right;
}node;

void allocNewNode(node*** np, element input){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->e = input;
    new_node->left = new_node->right = NULL;
    **np = new_node;
}

node* search(node** root, element input){
    if(!root) return root;

    int flag = strcmp(root->e.word, input.word);
    if(!flag){
        if(flag < 0)
            search(root->right, input);
        else search(root->left, input);
    }
    else return root;
}

void insertNode(node** root, element input){
    if(*root == NULL){
        allocNewNode(&root, input);
        return;
    }

    /*
    node** tmp = search(root, input);
    if(!tmp){
        allocNewNode(&tmp, input);
        return;
    }

    printf("[word]%s already exist!\n", input.word);
    */
}

void showMenu(){
    printf("\n*** i: insert, d: delete, s: search, p: print, q: quit ***\n");
    printf(">> ");
}

int main(int argc, char* argv[]){
    char command;
    node* root = NULL;
    node* tmp = NULL;
    element input;

    do{
        showMenu();
        command = getchar();
        getchar();
        switch(command){
            case 'i':
                printf("word: ");
                fgets(input.word, sizeof(input.word), stdin);
                input.word[strlen(input.word)-1] = 0;
                printf("meaning: ");
                fgets(input.meaning, sizeof(input.meaning), stdin);
                input.meaning[strlen(input.meaning)-1] = 0;
                insertNode(&root, input);
                break;
            case 'd':
                break;
            case 's':
                printf("word: ");
                fgets(input.word, sizeof(input.word), stdin);
                input.word[strlen(input.word)-1] = 0;
                tmp = search(root, input);
                if(!tmp)
                    //printf("%s가 사전에 있습니다.\n", input.word);
                    printf("[word %s]:[meaning: %s]", tmp->e.word, tmp->e.meaning);
                else printf("Search Failed...\n");
                break;
            case 'p':
                break;
            case 'q':
                break;

        }
    }while(command != 'q');

    return 0;
}
