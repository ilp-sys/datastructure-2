#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <stack>
#define MAX_INPUT_SIZE 100
using namespace std;

typedef struct{
    char key;
    int count;
}element;

typedef struct node{
    element e;
    node *left, *right;
}node;

node* allocNewNode(char c){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->e.key = c;
    new_node->e.count = 1;
    new_node->left = new_node->right = NULL;
    return new_node;
}

node* allocNewNode(char c, int count){//overload
    node* new_node = (node*)malloc(sizeof(node));
    new_node->e.key = c;
    new_node->e.count = count;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insertNodeBST(char c, node** root){
    if(!*root){
        *root = allocNewNode(c);
        return;
    }

    if((*root)->e.key > c)
        insertNodeBST(c, &((*root)->left));
    else if((*root)->e.key < c)
        insertNodeBST(c, &((*root)->right));
    else //((*root)->key == c)
        (*root)->e.count++;
}

void getElementCount(char* input, node** root){
    for(int i = 0; i < strlen(input); i++){
        insertNodeBST(input[i], root);
    }
}

void appendLastBST(char c, int count, node** root){
    if(*root == NULL){ 
        *root = allocNewNode(c, count);
        return;
    }
    appendLastBST(c, count, &((*root)->right));
}

int count = 0;
void deleteNodeBST(node** root, char c){
    if(!*root) return;

    if((*root)->e.key > c) deleteNodeBST(&((*root)->left), c);
    else if((*root)->e.key < c) deleteNodeBST(&((*root)->right), c);
    else{//key == c
        if((*root)->left == NULL){
            node *tmp = *root;
            *root = (*root)->right;
            count = tmp->e.count;
            free(tmp);
        }
        else if((*root)->right == NULL){
            node *tmp = *root;
            *root = (*root)->left;
            count = tmp->e.count;
            free(tmp);
        }
        else{
            node* tmp  = *root;
            while(tmp) tmp = tmp->left;
            (*root)->e.key = tmp->e.key;
            (*root)->e.count = tmp->e.count;
            count = tmp->e.count;
            free(tmp);
        }
    }
}


void printElement(node* root){ //print tree inorderly
    if(!root) return;

    printElement(root->left);

    if(root->e.key == '.') printf("PERIOD(%d)/ ", root->e.count);
    else if(root->e.key == ' ') printf("SPACE(%d)/ ", root->e.count);
    else printf("%c(%d)/ ", root->e.key, root->e.count);

    printElement(root->right);
}

void insertElementPQ(element e, vector<element>& heap){
    heap.push_back(e);
    
    int index = heap.size() -1;
    while(heap.size() != 1 && heap.size() != 2 && heap[index/2].count > e.count){
        element tmp = heap[index/2];
        heap[index/2] = heap[index];
        heap[index] = tmp;
        index /= 2;
    }
}

void heapsort(vector<element> &heap, node* root){
    stack<node*> s;
    node* curr = root;
    while(curr != NULL || s.empty() == false){
        while(curr != NULL){
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        insertElementPQ(curr->e, heap);
        curr = curr->right;
    }
}

void deleteElementPQ(vector<element> &heap){
    int parent, child;
    element item, temp;

    item = heap[1];
    temp = heap.back();
    heap.pop_back();

    parent = 1;
    child = 2;
    while(child <= heap.size() -1){
        if((child < heap.size() -1) && (heap[child].count > heap[child+1].count)) child++;
        if(temp.count <= heap[child].count) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }

    heap[parent] = temp;

    if(item.key == '.') printf("PERIOD(%d)/ ", item.count);
    else if(item.key == ' ') printf("SPACE(%d)/ ", item.count);
    else printf("%c(%d), ", item.key, item.count);
}

void printPriorQ(vector<element> heap){
    int iter = heap.size();
    for(int i = 1; i < iter; i++)
        deleteElementPQ(heap);
    printf("\n");
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
   deleteNodeBST(&root, '.'); // move position of period to the very right side
   if(count != 0) appendLastBST('.', count, &root);
   count = 0;
   deleteNodeBST(&root, ' '); // move position of space to the very right side
   if(count != 0) appendLastBST(' ', count, &root);
   count = 0;

   printElement(root);
   printf("\n");

   //heap sorting -> construct min heap - key: count
   vector<element> heap;
   element dummy = {0,0};
   heap.push_back(dummy);
   heapsort(heap, root);
    
   //print min-heap
   printPriorQ(heap);

   return 0;
}


