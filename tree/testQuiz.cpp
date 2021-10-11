#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char data;
    node* llink;
    node* rlink;
}node;

node* allocNewNode(char value, node* llink, node* rlink){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = value;
    new_node->llink = llink;
    new_node->rlink = rlink;
    return new_node;
}

void searchInOrder(node* root){
    if(root == NULL) return;
    searchInOrder(root->llink);
    printf("%c ", root->data);
    searchInOrder(root->rlink);
}

int main(int argc, char* argv[]){

    node* lnode = allocNewNode('a', NULL, NULL);
    node* rnode = allocNewNode('b', NULL, NULL);
    node* root = allocNewNode('+', lnode, rnode);

    printf("Search Inorderly: ");
    searchInOrder(root);
    printf("\n");

    return 0;
}
