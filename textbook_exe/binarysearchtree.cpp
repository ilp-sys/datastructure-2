#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct node{
    element key;
    struct node *left, *right;
}node;

node* search(node* node, int key){
    if(node == NULL) return NULL;

    if(key == node->key) return node;
    else if(key < node->key)
        return search(node->left, key);
    else 
        return search(node->right, key);
}

node* new_node(int key){
    node* tmp = (node*)malloc(sizeof(node));
    tmp->key= key;
    tmp->left = tmp->right = NULL;
    return tmp;
}

node* insert_node(node* node, int key){
    if (node == NULL) return new_node(key);
    
    if(key < node->key)
        node->left = insert_node(node->left, key);
    else if(key > node->key)
        node->right = insert_node(node->right, key);

    return node;
}

void inorder(node* root){
    if(root){
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

int main(int argc, char* argv[]){

    node* root = NULL;

    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);

    printf("Traverse binary search tree Inorderly: ");
    inorder(root);
    printf("\n\n");

    if(search(root, 30) != NULL)
        printf("이진 탐색 트리에서 30을 발견함\n");
    else
        printf("이진 탐색 트리에서 30을 발견못함\n");

    return 0;
}
