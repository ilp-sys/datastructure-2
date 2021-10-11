#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

Node* alloc_new_node(int data, Node* left, Node* right){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

Node* make_tree(){
    Node* node1 = alloc_new_node(7, NULL, NULL);
    Node* node2 = alloc_new_node(4, NULL, NULL);
    Node* node3 = alloc_new_node(5, NULL, node1);
    Node* node4 = alloc_new_node(6, NULL, NULL);
    Node* node5 = alloc_new_node(2, node2, NULL);
    Node* node6 = alloc_new_node(3, node3, node4);
    Node* node7 = alloc_new_node(1, node5, node6);
    return node7;
}

void level_order(Node* root){
    printf("[Level order] ");
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        root = q.front();
        printf("%d ", root->data);
        q.pop();
        if(root->left)
            q.push(root->left);
        if(root->right)
            q.push(root->right);
    }
    printf("\n");
}

int count = 0;
void pre_order(Node* root){
    count++;
    if(count == 1) printf("[Pre order] ");
    if(!root)
        return;
    printf("%d ", root->data);
    pre_order(root->left);
    pre_order(root->right);
}

void get_leafnodes(queue<int> *q, Node* root){
    if(!root) return;
    if(root->left == NULL && root->right == NULL)
        (*q).push(root->data);
    else{ 
        get_leafnodes(q, root->left);
        get_leafnodes(q, root->right);
    }
}

void find_leafnodes(Node* root){
    printf("\n[Leaf nodes] ");
    queue<int> q;
    get_leafnodes(&q, root);
    while(!q.empty()){
        printf("%d ", q.front());
        q.pop();
    }
    printf("\n");
}

void find_max(Node* root){
    int max = 0;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        root = q.front();
        q.pop();
        if(max < root->data) max = root->data;
        if(root->left) q.push(root->left);
        if(root->right) q.push(root->right);
    }
    printf("[Max] %d\n", max);
}

int main(void){
    Node* root = make_tree();
    level_order(root);
    pre_order(root);
    find_leafnodes(root);
    find_max(root);
    return 0;
}
