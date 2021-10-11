#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

typedef struct{
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];
}element;

typedef struct node{
    element key;
    node *left, *right;
}node;

node* new_node(element key){
    node* tmp = (node*)malloc(sizeof(node));
    tmp->key = key;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

int compare(element e1, element e2){
    return strcmp(e1.word, e2.word);
}

node* insert_node(node* node, element key){
    if(node == NULL) return new_node(key);

    if(compare(key, node->key) < 0)
        node->left = insert_node(node->left, key);
    else if(compare(key, node->key) > 0)
        node->right = insert_node(node->right, key);

    return node;
}

node* min_value_node(node* root){
    while(root != NULL)
        root = root-> left;
    return root;
}

node* delete_node(node* root, element key){
    if(root == NULL)
        return root;

    if(compare(key, root->key) < 0)
        root->left = delete_node(root->left, key);
    else if(compare(key, root->key) > 0)
        root->right = delete_node(root->right, key);

    else{ //if compare(key, root->key) == 0
        if(root->left = NULL){
            node* tmp = root->right;
            free(root);
            return tmp;
        }
        else if(root->right == NULL){
            node* tmp = root->left;
            free(root);
            return tmp;
        }
        //when both of the subtrees are not null
        node* tmp  = min_value_node(root->right);
        root->key = tmp->key;
        root->right = delete_node(root->right, tmp->key);
    }
    return root;
}

node* search(node* root, element key){
    node *p = root;
    while(p != NULL){
        if(!compare(key, p->key))
            return p;
        else if(compare(key, p->key)<0)
            p = p->left;
        else if(compare(key, p->key)>0)
            p = p->right;
    }
    return p;
}

void display(node* root){
    node* p = root;
    if(p != NULL){
        printf("(");
        display(p->left);
        printf("%s.:%s", p->key.word, p->key.meaning);
        display(p->right);
        printf(")");
    }
}

void help(){
    printf("\n*** i: insert, d: delete, s: search, p: print, q: quit ****\n");
}

int main(int argc, char* argv[]){

    char command;
    element e;
    node *root = NULL;
    node *tmp = NULL;

    do{
        help();
        command = getchar();
        getchar(); //버퍼 받기
        switch(command){
            case 'i':
                printf("word: ");
                fgets(e.word, sizeof(e.word), stdin);
                printf("meaning: ");
                fgets(e.meaning, sizeof(e.meaning), stdin);
                root = insert_node(root, e);
                break;
           case 'd':
                printf("word: ");
                fgets(e.word, sizeof(e.word), stdin);
                root = delete_node(root, e);
                break;
           case 's':
                printf("word: ");
                fgets(e.word, sizeof(e.word), stdin);
                tmp = search(root, e);
                if(tmp != NULL)
                    printf("meaning: %s\n", e.meaning);
                break;
           case 'p':
                display(root);
                printf("\n");
                break;
           case 'q':
                break;

        }
    }while(command != 'q');

    return 0;
}

