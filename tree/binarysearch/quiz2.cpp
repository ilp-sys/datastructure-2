#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

typedef struct node{
    int val;
    node *left, *right;
}node;

node* allocNewNode(int input){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->val = input;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insertNode(node** root, int input){
    if(!*root) *root = allocNewNode(input);

    if((*root)->val > input) insertNode(&((*root)->left), input);
    else if((*root)->val < input) insertNode(&((*root)->right), input);
}

int searchNode(int count, node* root, int input){
    while(root != NULL){
        if(root->val == input){
            count++;
            break;
        }
        else if(root->val > input){
            count++;
            root = root->left;
            //searchNode(count, root->left, input);
        }
        else{//(root->val < input){
            count++;
            root = root->right;
            //searchNode(count, root->right, input);
        }
    }
    if(!root) return 0;
    return count;
}

void levelOrder(node* root){
    queue<node*> q;
    if(!root) return;

    q.push(root);
    while(!q.empty()){
        root = q.front();
        q.pop();
        printf("[%d] -", root->val);
        if(root->left) q.push(root->left);
        if(root->right) q.push(root->right);
    }

    printf("\n");
}

int free_count = 0;
void freeNode(node** root){
    queue<node*> q;
    if(!*root) return;

    q.push(*root);
    while(!q.empty()){
        *root = q.front();
        node* left = NULL;
        node* right = NULL;
        if((*root)->left) left = (*root)->left;
        if((*root)->right) right = (*root)->right;
        printf("%d 노드 free 됨.\n", (*root)->val);
        free(*root);
        free_count++;
        q.pop();
        if(left) q.push(left);
        if(right)q.push(right);
    }
}

void showMenu(){
    printf("\n1.입력");
    printf("\n2.탐색");
    printf("\n3.Level Order");
    printf("\n4.종료");
    printf("\n번호를 넣으세요: ");
}

int main(int argc, char* argv[]){
    
    node* root = NULL;
    int flag = 1;
    int menu = 0;
    int input = 0;
    
    while(flag){
        showMenu();
        scanf("%d", &menu);
        switch(menu){
            case 1:
                while(input != -1){
                    printf("입력(종료는 -1):");
                    scanf("%d", &input);
                    if(input == -1) continue;
                    insertNode(&root, input);
                }
                break;
            case 2:{
                printf("탐색할 노드?: ");
                scanf("%d", &input);
                int tmp = searchNode(0, root, input);
                if(tmp == 0) printf("%d는 존재하지 않습니다.\n", input);
                else printf("%d는 %d회 탐색으로 발견\n", input, tmp);
                break;
                }
            case 3:
                levelOrder(root);
                break;
            case 4:
                freeNode(&root);
                printf("총 %d개의 노드가 free 됨.\n", free_count);
                printf("[종료]\n");
                flag = 0;
                break;
        }
    }

    return 0;
}
