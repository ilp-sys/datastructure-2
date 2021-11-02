#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

typedef struct e_node{
    string word;
    vector<string> meaning;
    e_node *left, *right;
}e_node;

typedef struct k_node{
    string word;
    string meaning;
    k_node *left, *right;
}k_node;

e_node* addNewNode(string word, vector<string> meaning){
    e_node* new_node = (e_node*)malloc(sizeof(e_node));
    new_node->word = word;
    new_node->meaning = meaning;
    new_node->left = new_node->right = NULL;
    return new_node;
}

k_node* addNewNode(string word, string meaning){
    k_node* new_node = (k_node*)malloc(sizeof(k_node));
    new_node->word = word;
    new_node->meaning = meaning;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void addNewWord(e_node node_buffer, e_node** e_root){
    if(!*e_root){
        *e_root = addNewNode(node_buffer.word, node_buffer.meaning);
        return;
    }

    if((*e_root)->word.compare(node_buffer.word) < 0)
        addNewWord(node_buffer, &((*e_root)->right));
    else if((*e_root)->word.compare(node_buffer.word) > 0)
        addNewWord(node_buffer, &((*e_root)->left));
    else{
        printf("%s already exist in dictionary!\n", node_buffer.word.c_str());
    }
}

void addNewWord(k_node node_buffer, k_node** k_root){//overload....
    if(!*k_root){
        *k_root = addNewNode(node_buffer.word, node_buffer.meaning);
        return;
    }

    if((*k_root)->word.compare(node_buffer.word) < 0)
        addNewWord(node_buffer, &((*k_root)->right));
    else if((*k_root)->word.compare(node_buffer.word) > 0)
        addNewWord(node_buffer, &((*k_root)->left));
    else{
        printf("%s already exist in dictionary!\n", node_buffer.word.c_str());
    }
}

e_node* makeEngBST(ifstream& dict_file, e_node* e_root){
    printf( "파일 로드 중...\n");

    int flag = 1;
    string tmp;

    while(!dict_file.eof()){
        e_node node_buffer;
        
        if(flag) getline(dict_file, node_buffer.word);
        else node_buffer.word = tmp;

        while(!dict_file.eof()){
            getline(dict_file, tmp);
            if((tmp[0] >= 65 && tmp[0] <= 90) || (tmp[0] >= 97 && tmp[0] <= 122)){
                flag = 0;
                break;
            }
            node_buffer.meaning.push_back(tmp);
        }

        addNewWord(node_buffer, &e_root);
    }

    return e_root;
}

k_node* makeKorBST(ifstream& dict_file, k_node* k_root){
    int flag = 1;
    string tmp;

    while(!dict_file.eof()){
        k_node node_buffer;

        if(flag) getline(dict_file, node_buffer.word);
        else node_buffer.word = tmp;

        while(!dict_file.eof()){
            getline(dict_file, tmp);
            if((tmp[0] >= 65 && tmp[0] <= 90) || (tmp[0] >= 97 && tmp[0] <= 122)){
                flag = 0;
                break;
            }
            node_buffer.meaning = tmp;
            addNewWord(node_buffer, &k_root);
        }
    }
    printf("데이터 로드 완료.\n");
    return k_root;
}

int is_terminal(e_node* root){
    return (root->left == NULL && root->right == NULL) ? 1 : 0;
}

int is_terminal(k_node* root){//overload
    return (root->left == NULL && root->right == NULL) ? 1 : 0;
}

void searchEK(e_node* e_root){
    if(!e_root) return;

    printf("영어 입력: ");
    string word2find;
    getline(cin, word2find);

    printf("검색과정: ");
    while(1){
        if(e_root->word.compare(word2find) == 0){
            cout << e_root->word << " : ";
            for(int i = 0; i < e_root->meaning.size(); i++)
                cout << e_root->meaning[i] << "  ";
            printf("\n");
            return;
        }
        if(is_terminal(e_root)) break;

        if(e_root->word.compare(word2find) > 0){
            cout << e_root->word << " - ";
            e_root = e_root->left;
        }
        else if(e_root->word.compare(word2find) < 0){
            cout << e_root->word << " - ";
            e_root = e_root->right;
        }
    }
    printf("none\n");
}

void searchKE(k_node* k_root){
    if(!k_root) return;

    printf("한국어 입력: ");
    string word2find;
    getline(cin, word2find);

    printf("검색과정:");
    while(1){
        if(k_root->meaning.compare(word2find) == 0){
            cout << k_root->meaning << " : " << k_root->word << endl;
            return;
        }
        if(is_terminal(k_root)) break;
        
        if(k_root->meaning.compare(word2find) > 0){
            cout << k_root->meaning << " - ";
            k_root = k_root->left;
        }
        else if(k_root->meaning.compare(word2find) < 0){
            cout << k_root->meaning << " - ";
            k_root = k_root->right;
        }
    }
    printf("없음.\n");
}

e_node* findMin(e_node* e_root){
    if(!e_root) return e_root;
    findMin(e_root->left);
}

void deleteWord(e_node** e_root, string word2del){
    if((*e_root)->word.compare(word2del) > 0)
        deleteWord(&((*e_root)->left), word2del);
    else if((*e_root)->word.compare(word2del) < 0)
        deleteWord(&((*e_root)->right), word2del);
    else{
        if((*e_root)->left == NULL){
            e_node* tmp = *e_root;
            *e_root = (*e_root)->right;
            free(tmp);
        }
        else if((*e_root)->right == NULL){
            e_node* tmp = *e_root;
            *e_root = (*e_root)->right;
            free(tmp);
        }
        else{
            e_node* tmp = findMin(*e_root);
            (*e_root)->word = tmp->word;
            (*e_root)->meaning = tmp->meaning;
            free(tmp);
        }
    }
}

void testPerf(){}

void saveDict(char* file_name, e_node* e_root){
    ofstream dict_file;
    dict_file.open(file_name);
    if(!dict_file.is_open()){fprintf(stderr, "Can not open file %s\n", file_name); return;}

    queue<e_node*> q;
    q.push(e_root);

    while(!q.empty()){
        e_root = q.front();
        q.pop();

        dict_file << e_root->word << endl;
        for(int i = 0; i < e_root->meaning.size(); i++)
            dict_file << e_root->meaning[i] << endl;

        if(e_root->left) q.push(e_root->left);
        if(e_root->right) q.push(e_root->right);
    }
    dict_file.close();
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
    e_node* e_root = NULL;
    k_node* k_root = NULL;

    ifstream dict_file;
    dict_file.open(argv[1]);
    if(!dict_file.is_open()){fprintf(stderr, "Can not open file %s\n", argv[1]); return -1;}

    e_root = makeEngBST(dict_file, e_root);
    k_root = makeKorBST(dict_file, k_root);

    dict_file.close();

    //user operation
    int flag = 1;
    int menu = 0;
    while(flag){
        showMenu();
        scanf("%d", &menu);
        getchar();
        switch(menu){
            case 1:
                searchEK(e_root);
                break;
            case 2:
                searchKE(k_root);
                break;
            case 3:{
                       string buffer, tocken;
                       vector<string> input;
                       printf("추가할 단어(영어 한글): ");
                       getline(cin, buffer);
                       stringstream ss(buffer);

                       while(getline(ss, tocken, ' '))
                           input.push_back(tocken);

                       cout << "Input word: " << input[0] << ", Input meaning: "  << input[1] << endl;;

                       vector<string> input_meaning;
                       input_meaning.push_back(input[1]);
                       e_node node_buffer = {input[0], input_meaning, NULL, NULL};
                       addNewWord(node_buffer, &e_root);
                       cout << "등록완료" << endl;
                       break;
                   }
            case 4:{
                       cout << "삭제할 단어: "; 
                       string word2del;
                       getline(cin, word2del);
                       deleteWord(&e_root, word2del);
                       cout << "등록완료" << endl;
                   }
                break;
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
