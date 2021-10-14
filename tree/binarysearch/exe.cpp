#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    node *right, *left;
}node;

node* allocNewNode(int val, node* left, node* right){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->val = val;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

node* make_tree(){
    node* node2 = allocNewNode(4, NULL, NULL);
    node* node3 = allocNewNode(6, NULL, NULL);
    node* node1 = allocNewNode(5, node2, node3);
    return node1;
}

node* searchNode(node* root, int val){
    if(!root) return root;

    while(root){
        if(root->val == val) return root;
        else if(root->val < val) root = root->right;
        else root = root->left;
    }
    return root;
}

void insertNode(node** root, int val){
    if(!*root){
        *root = allocNewNode(val, NULL, NULL);
        return;
    }

    if((*root)->val > val)
        insertNode(&((*root)->left), val);
    else if((*root)->val < val)
        insertNode(&((*root)->right), val);
    else{
        printf("%d already exisit!\n", val);
        return;
    }
}

node* findMin(node* root){
    if (!root) return root;
    findMin(root->left);
}

void deleteNode(node** root, int val){
    if((*root)->val > val)
        deleteNode(&((*root)->left), val);
    else if((*root)->val < val)
        deleteNode(&((*root)->right), val);
    else{
        if((*root)->left == NULL){
            node *tmp = *root;
            *root = (*root)->right;
            free(tmp);
        }
        else if((*root)->right == NULL){
            node *tmp = *root;
            *root = (*root)->left;
            free(tmp);
        }
        else{
            node* tmp = findMin(*root);
            (*root)->val = tmp->val;
            free(tmp);
        }
    }
}


int main(int argc, char* argv[]){
    node* root = make_tree();

    if(searchNode(root, 4))
        printf("%d exits\n", 4);
    insertNode(&root, 10);
    if(searchNode(root, 10))
        printf("%d exist\n", 10);
    deleteNode(&root, 10);
    if(searchNode(root, 10))
        printf("%d exist\n", 10);

    return 0;
}
