#include <stdio.h>
#include <stdlib.h>

typedef struct card{
    int num;
    int count;
    card* right;
    card* left;
}card;

card* addNewNode(int tmp){
    card* new_node = (card*)malloc(sizeof(card));
    new_node->num = tmp;
    new_node->count = 1;
    return new_node;
}

void addBST(card** root, int tmp){
    if(!*root){
        *root = addNewNode(tmp);
        return;
    }

    if((*root)->num > tmp)
        addBST(&((*root)->left), tmp);
    else if((*root)->num < tmp)
        addBST(&((*root)->right), tmp);
    else{
        (*root)->count++;
        return;
    }
}

void searchBST(card* root, int tmp){
    if(!root){
        printf("0");
        return;
    }

    if(root->num > tmp)
        searchBST(root->left, tmp);
    else if(root->num < tmp)
        searchBST(root->right, tmp);
    else {
        printf("%d", root->count);
        return;
    }
}

int main(int argc, char* argv[]){

    card* root = NULL;

    int card_num = 0;
    scanf("%d", &card_num);

    for(int i = 0; i < card_num; i++){
        int tmp = 0;
        scanf("%d", &tmp);
        addBST(&root, tmp);
    }

    int search_num = 0;
    scanf("%d", &search_num);

    for(int i = 0; i < search_num; i++){
        int tmp = 0;
        scanf("%d", &tmp);
        searchBST(root, tmp);
        if(i != search_num-1) printf(" ");
    }

    return 0;
}
