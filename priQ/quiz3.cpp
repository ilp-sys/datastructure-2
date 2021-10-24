#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stack>
#define MAX_INPUT_SIZE 100
using namespace std;

typedef struct node{
    char key;
    int count;
    node *left, *right;
}node;

node* allocNewNode(char c, node* left, node* right){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->key = c;
    new_node->count = 1;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

void insertNodeBST(char c, node** root){
    if(!*root)
        *root = allocNewNode(c, NULL, NULL);

    if((*root)->key > c)
        insertNodeBST(c, &((*root)->left));
    else if((*root)->key < c)
        insertNodeBST(c, &((*root)->right));
    else //((*root)->key == c)
        (*root)->count++;
}

void getElementCount(char* input, node** root){
    for(int i = 0; i < strlen(input); i++){
        insertNodeBST(input[i], root);
    }
}

void appendLastBST(element e, node** root){
    while(*root) *root = (*root)->right;
    *root = allocNewNode(e, NULL, NULL);
}

/*
element deleteNodeBST(node** root, char c){
    element e;

    if((*root)->e.key > c) deleteNodeBST(&((*root)->left), c);
    else if((*root)->e.key < c) deleteNodeBST(&((*root)->right), c);
    else{//key == c
        if((*root)->left){
            node *tmp = *root;
            e = (*root)->e;
            *root = (*root)->right;
            free(tmp);
        }
        else if((*root)->right){
            node *tmp = *root;
            e = (*root)->e;
            *root = (*root)->left;
            free(tmp);
        }
        else{
            node* tmp  = *root;
            e = (*root)->e;
            while(tmp) tmp = tmp->left;
            (*root)->e = tmp->e;
            free(tmp);
        }
    }
    return e;
}
*/

int isTerminal(node* root){
    return (root->left == NULL && root->right == NULL) ? 1 : 0;
}

void reformBST(node** root, char c){//if there's node we're looking for, append it last and delete it
    
}

void printElement(node* root){ //print tree inorderly
    if(!root) return;

    printElement(root->left);

    if(root->key == '.') printf("PERIOD(%d)/ ", root->count);
    else if(root->key == ' ') printf("SPACE(%d)/ ", root->count);
    else printf("%c(%d)/ ", root->key, root->count);

    printElement(root->right);
}

void insertElementPQ(element e, vector<element>* heap){
    heap->push_back(e);
    
    int index = heap->size();
    while(heap->size() != 1 && (*heap)[index/2].count < e.count){
        element tmp = (*heap)[index/2];
        (*heap)[index/2] = (*heap)[index];
        (*heap)[index] = tmp;
        index /= 2;
    }
}

void heapsort(vector<element> &heap, node* root){
    stack<node*> s;
    s.push(root);
    node* curr = s.top();

    while(!s.empty()){
        while(curr){
            curr = curr->left;
            s.push(curr);
        }
        curr = s.top();
        insertElementPQ(curr->e, &heap);
        s.pop();
        curr = curr->right;
    }
}

void deleteElementPQ(vector<element> &heap){
    printf("%c(%d), ", heap[1].key, heap[1].count);
    heap[1] = heap.back();
    heap.pop_back();

    int parent = 1;
    int child = parent*2;
    while(child <= heap.size()){
        if((child < heap.size()) && (heap[child].count > heap[child+1].count))
            child++;
        if((heap[child].count < heap[parent].count)){
            element tmp = heap[parent];
            heap[parent] = heap[child];
            heap[child] = tmp;
        }
    }
}

void printPriorQ(vector<element> heap){
    for(int i = 0; i < heap.size(); i++)
        deleteElementPQ(heap);
}

int main(int argc, char* argv[]){

    //get input string
   char input[MAX_INPUT_SIZE];
   printf("Input String: ");
   fgets(input, sizeof(input), stdin);
   input[strlen(input)-1] = '\0';

   //get element count -> construct binary search tree - key:alphabet & '.' & ' '
   /*
      | char | ascii code(dec) |
      |  ' ' |      32         |
      |  '.' |      46         |
      |  a-z |    97 - 122     |
    */
   node* root = NULL;
   getElementCount(input, &root);
   
   //print element count -> traverse inorderly
   reformBST(&root, '.'); // move position of period to the very right side
   reformBST(&root, ' '); // move position of space to the very right side
   printElement(root);
   printf("\n");

   /*
   //heap sorting -> construct min heap - key: count
   vector<element> heap;
   element dummy = {'\0', -999};
   heap.push_back(dummy);
   heapsort(heap, root);
    
   //print min-heap
   printPriorQ(heap);
   */

   return 0;
}


