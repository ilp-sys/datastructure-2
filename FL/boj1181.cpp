#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

typedef struct{
    char string[51];
    int length;
}array;

array sort[20001]; //temporary array for sorting
void merge(int left, int right, int mid, array* input){
    int i = left, j = mid + 1, k = left;

    while(i <= mid && j <= right){
        if(input[i].length < input[j].length)
            sort[k++] = input[i++];
        else if(input[i].length == input[j].length){
            if(strcmp(input[i].string, input[j].string) < 0)
                sort[k++] = input[i++];
            else 
                sort[k++] = input[j++];
        }
        else// input[i].length > input[j].length
            sort[k++] = input[j++];
    }

    if(i <= mid)
        while(i <= mid)
            sort[k++] = input[i++];
    else 
        while(j <= right)
            sort[k++] = input[j++];

    for(k = left; k <= right; k++) //sort array의 내용(정렬 완료)를 다시 input에 넣기
        input[k] = sort[k];
}

void merge_sort(int left, int right, array *input){
    if(left < right){//left == right인 경우 return의 역할
        int mid = (left + right)/2;
        merge_sort(left, mid, input);
        merge_sort(mid + 1, right, input);
        merge(left, right, mid, input);
    }
}

int main(int argc, char* argv[]){
    //get user input
    int n = 0;
    scanf("%d", &n);

    array input[n];

    for(int i =0; i < n; i++){
        memset(input[i].string, 0, 51);
        scanf("%s", input[i].string);
        input[i].length = strlen(input[i].string);
    }

    //sorting
    merge_sort(0, n-1, input);

    //print output - do not prit duplicated word
    for(int i = 0; i < n; i++){
        if(i == 0)
            printf("%s\n", input[i].string);
        else
            if(strcmp(input[i-1].string, input[i].string)!= 0)
                printf("%s\n", input[i].string);
    }

    return 0;
}


