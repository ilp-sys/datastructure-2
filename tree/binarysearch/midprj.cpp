#include <stdio.h>
#include <cstring>
#include <stdlib.h>
//#include <vector>
#include <queue>
#define MAX_WORD_SIZE 100
using namespace std;

typedef struct node{
    char word[MAX_WORD_SIZE];
    //vector<char*> meaning;
    char meaning[MAX_WORD_SIZE];
    node* left;
    node* right;
}node;

node* addNewNode(char* word, char* meaning){
    node* new_node = (node*)malloc(sizeof(node));
    strcpy(new_node->word, word);
    //new_node->meaning.push_back(meaning);
    strcpy(new_node->meaning, meaning);
    new_node->left = new_node->right = NULL;
    return new_node;
}

//<---! implementation for additional point.. --->
void searchKE(node* root){}
void testPerf(){};
//<-- end here -->

void addNewWord(char* word_buffer, char* meaning_buffer, node** root){
    if(!*root){
        *root = addNewNode(word_buffer, meaning_buffer);
        return;
    }

    if(strcmp((*root)->word, word_buffer) > 0)
        addNewWord(word_buffer, meaning_buffer, &((*root)->left));
    else if(strcmp((*root)->word, word_buffer) < 0)
        addNewWord(word_buffer, meaning_buffer, &((*root)->right));
    else{
        printf("%s already exist!\n", word_buffer);
        return;
    }
}

node* makeDictTree(FILE* fp, node* root){
    printf("파일 로드 중....\n");
    while(!feof(fp)){
        char word_buffer[MAX_WORD_SIZE];
        char meaning_buffer[MAX_WORD_SIZE];

        fgets(word_buffer, sizeof(word_buffer), fp);
        fgets(meaning_buffer, sizeof(meaning_buffer), fp);

        word_buffer[strlen(word_buffer)-1] = '\0';
        meaning_buffer[strlen(meaning_buffer)-1] = '\0';

        addNewWord(word_buffer, meaning_buffer, &root);
    }
    printf("데이터 로드 완료.\n");
    return root;
}

int isTerminal(node *root){
    return (root->left == NULL && root->right == NULL) ? 1 : 0;
}

void searchEK(node* root){
    if(!root) return;

    printf("영어입력: ");
    char word2find[MAX_WORD_SIZE];
    fgets(word2find, sizeof(word2find), stdin);
    word2find[strlen(word2find)-1] = '\0';
    
    printf("검색과정: ");
    while(root){
        if(strcmp(root->word, word2find) == 0){
            //printf("%s : %s\n", root->word, root->meaning.front());
            printf("%s : %s\n", root->word, root->meaning);
            return;
        }
        if(isTerminal(root)) break;

        if(strcmp(root->word, word2find) > 0){
            printf("%s - ", root->word);
            root = root->left;
        }
        else if(strcmp(root->word, word2find) < 0){
            printf("%s - ", root->word);
            root = root->right;
        }
    }
    printf(" 없음\n");
}

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
            strcpy((*root)->meaning, tmp->meaning);
            //(*root)->meaning = tmp->meaning; //copying vector
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

        fputs(root->word, fp);
        fputs("\n", fp);
        fputs(root->meaning, fp);
        fputs("\n", fp);
        //fputs(root->meaning.front(), fp);

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
        printf("Usage)./a.out engkor.dat\n");
        return -1;
    }

    FILE* fp = fopen(argv[1], "r");
    if(!fp){
        fprintf(stderr, "Can not open file %s\n", argv[1]);
        return -1;
    }

    node* root = NULL;
    root = makeDictTree(fp, root);
    fclose(fp);

    int flag = 1;
    int menu = 0;
    while(flag){
        showMenu();
        scanf("%d", &menu);
        getchar();
        switch(menu){
            case 1:
                searchEK(root);
                break;
            case 2:
                searchKE(root);
                break;
            case 3:{
                       printf("추가할 단어(영어 한글): ");
                       char e_tmp[MAX_WORD_SIZE];
                       char k_tmp[MAX_WORD_SIZE];
                       //fscanf(stdin, "%s", e_tmp);
                       //fscanf(stdin, "%s", e_tmp);
                       scanf("%s", e_tmp);
                       scanf("%s", k_tmp);
                       printf("input eng: %s , kor: %s\n", e_tmp, k_tmp);
                       addNewWord(e_tmp, k_tmp, &root);
                       printf("등록완료\n");
                       break;
                   }
            case 4:{
                       printf("삭제할 단어: ");
                       char word2del[MAX_WORD_SIZE];
                       fscanf(stdin, "%s", word2del);
                       deleteWord(&root, word2del);
                       printf("삭제 완료\n");
                   }
                break;
            case 5:
                testPerf();
                break;
            case 6:
                saveDict(argv[1], root);
                flag = 0;
                break;
        }
    }

    return 0;
}
