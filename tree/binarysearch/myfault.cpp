#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <queue>
#define MAX_WORD_SIZE 256
#define MAX_MEANING_COUNT 10 
using namespace std;

typedef struct node{
    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_COUNT][MAX_WORD_SIZE];
    node *left, *right;
}node;

int get2DLen(char (*array)[MAX_WORD_SIZE]){
    int count = 0;
    int row = MAX_MEANING_COUNT;
    for(int i = 0; i < row; i++){
        if(strcmp(array[i], "endhere") == 0) break;
        else count++;
    }
    return count;
}

node* addNewNode(char* word, char (*meaning)[MAX_WORD_SIZE]){
    node* new_node = (node*)malloc(sizeof(node));
    strcpy(new_node->word, word);
    int len  = get2DLen(meaning);
    for(int i = 0; i < len; i++)
        strcpy(new_node->meaning[i], meaning[i]);
    new_node->left = new_node->right = NULL;
    return new_node;
}

void addNewWord(char* word, char (*meaning)[MAX_WORD_SIZE], node** e_root){
    if(!*e_root){
        *e_root = addNewNode(word, meaning);
        return;
    }

    if(strcmp((*e_root)->word, word) > 0)
        addNewWord(word, meaning, &((*e_root)->left));
    else if(strcmp((*e_root)->word, word) < 0)
        addNewWord(word, meaning, &((*e_root)->right));
    else 
        printf("%s already exist in dictionary!\n", (*e_root)->word);
}

node* makeEngBST(char* file_name, node* e_root){
    printf("파일 로드 중...\n");
  
    FILE* fp = fopen(file_name, "r");
    if(!fp){
        fprintf(stderr, "Error) Can not open file %s.\n", file_name);
        exit(-1);
    }

    int flag = 1;
    char tmp[MAX_WORD_SIZE];

    while(!feof(fp)){
        char word_tmp[MAX_WORD_SIZE];
        char meaning_tmp[MAX_MEANING_COUNT][MAX_WORD_SIZE];
        int i = 0;

        if(flag){
            fgets(word_tmp, sizeof(word_tmp), fp);
            word_tmp[strlen(word_tmp)-1] = '\0';
        }
        else strcpy(word_tmp, tmp);

        while(!feof(fp)){
            fgets(tmp, sizeof(tmp), fp);
            tmp[strlen(tmp)-1] = '\0';
            if((tmp[0] >= 65 && tmp[0] <= 90) || (tmp[0] >= 97 && tmp[0] <= 122)){
                strcpy(meaning_tmp[i++], "endhere");
                flag = 0;
                break;
            }
            strcpy(meaning_tmp[i++], tmp);
        }

        addNewWord(word_tmp, meaning_tmp, &e_root);
    }
    
    fclose(fp);
    return e_root;
}

node* makeKorBST(char* file_name, node* k_root){

    FILE* fp = fopen(file_name, "r");
    if(!fp){
        fprintf(stderr, "Error) Can not open file %s.\n", file_name);
        exit(-1);
    }

    int flag = 1;
    char tmp[MAX_WORD_SIZE];

    while(!feof(fp)){
        char word_tmp[MAX_WORD_SIZE];
        char meaning_tmp[MAX_MEANING_COUNT][MAX_WORD_SIZE];

        if(flag){
            fgets(meaning_tmp[0], sizeof(meaning_tmp[0]), fp);
            meaning_tmp[0][strlen(meaning_tmp[0])-1] = '\0';
            strcpy(meaning_tmp[1], "endhere");
        }
        else{
            strcpy(meaning_tmp[0], tmp);
            strcpy(meaning_tmp[1], "endhere");
        }

        while(!feof(fp)){
            fgets(tmp, sizeof(tmp), fp);
            tmp[strlen(tmp)-1] = '\0';
            if((tmp[0] >= 65 && tmp[0] <= 90) || (tmp[0] >= 97 && tmp[0] <= 122)){
                flag = 0;
                break;
            }
            strcpy(word_tmp, tmp);
            addNewWord(word_tmp, meaning_tmp, &k_root);
        }
    }
     
    printf("데이터 로드 완료.\n");
    fclose(fp);
    return k_root;
}

int is_terminal(node* root){
    return (root->left == NULL && root->right == NULL);
}

void search(node* root){
    if(!root) return;
    
    printf("찾을 단어 입력: ");
    char word2find[MAX_WORD_SIZE];
    fgets(word2find, sizeof(word2find), stdin);
    word2find[strlen(word2find)-1] = '\0';
    
    printf("검색과정: ");
    while(1){
        if(strcmp(root->word, word2find) == 0){
            printf("%s : ", root->word);
            int len = get2DLen(root->meaning);
            for(int i = 0; i < len; i++)
                printf("%s ", root->meaning[i]);
            printf("\n");
            return;
        }

        if(is_terminal(root)) break;

        if(strcmp(root->word, word2find) > 0){
            printf("%s - ", root->word);
            root = root->left;
        }
        else if(strcmp(root->word, word2find) < 0){
            printf("%s - ", root->word);
            root = root->right;
        }
    }
    printf("없음\n");
}

void testPerf(){}

node* findMin(node* root){
    if(!root) return root;
    findMin(root->left);
}

void deleteWord(node** root, char* word2del){
    if(strcmp((*root)->word, word2del) > 0)
        deleteWord(&((*root)->left), word2del);
    else if(strcmp((*root)->word, word2del) < 0)
        deleteWord(&((*root)->right), word2del);
    else{
        if((*root)->left == NULL){
            node* tmp = *root;
            *root = (*root)->right;
            free(tmp);
        }
        else if((*root)->right == NULL){
            node* tmp = *root;
            *root = (*root)->left;
            free(tmp);
        }
        else{
            node* tmp = findMin(*root);
            strcpy((*root)->word, tmp->word);
            int len = get2DLen(tmp->meaning);
            for(int i = 0; i < len; i++)
                strcpy((*root)->meaning[i], tmp->meaning[i]);
            free(tmp);
        }
    }
}

void saveDict(char* file_name, node* root){
    FILE* fp = fopen(file_name, "w");
    if(!fp){
        fprintf(stderr, "Can not open file %s\n", file_name);
        return;
    }

    queue<node*> q;
    q.push(root);

    while(!q.empty()){
        root = q.front();
        q.pop();

        fputs(root->word, fp); fputs("\n", fp);

        int len = get2DLen(root->meaning);
        for(int i = 0; i < len; i++){
            fputs(root->meaning[i], fp); fputs("\n", fp);
        }

        if(root->left) q.push(root->left);
        if(root->right) q.push(root->right);
    }
    fclose(fp);
}


void showMenu(){
    printf("\n****MENU****\n");
    printf("1. eng->kor search/ 2.kor->eng search/ 3.add word/ 4.delete word/ 5.test performance/ 6. quit\n");
    printf(">> ");
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Wrong Input...\n");
        printf("Usage) ./a.out [file_name]\n");
        return -1;
    }

    //init & make word bst
    node* e_root = NULL;
    node* k_root = NULL;

    e_root = makeEngBST(argv[1], e_root);
    k_root = makeKorBST(argv[1], k_root);

    //user operatopm
    int flag = 1;
    int menu = 0;
    while(flag){
        showMenu();
        scanf("%d", &menu);
        getchar();
        switch(menu){
            case 1:
                search(e_root);
                break;
            case 2:
                search(k_root);
                break;
            case 3:{
                       printf("추가할 단어(영어 한글): ");
                       char word[MAX_WORD_SIZE];
                       char meaning[MAX_MEANING_COUNT][MAX_WORD_SIZE];
                       scanf("%s %s", word, meaning[0]);
                       printf("input eng: %s, kor: %s\n", word, meaning[0]);
                       strcpy(meaning[1], "endhere");
                       addNewWord(word, meaning, &e_root);
                       printf("등록완료\n");
                       break;
                   }
            case 4:{
                       printf("삭제할 단어: ");
                       char word2del[MAX_WORD_SIZE];
                       scanf("%s", word2del);
                       deleteWord(&e_root, word2del);
                       printf("삭제완료\n"); 
                       break;
                   }
            case 5:
                testPerf();
                break;
            case 6:
                saveDict(argv[1], e_root);
                flag = 0;
                break;
        }
    }

    return 0;
}
