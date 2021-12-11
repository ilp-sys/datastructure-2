#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x, y ,t) ((t)=(x), (x)=(y), (y)=(t))

int list[MAX_LIST];
int n;

void selectionSort(int list[], int n){
    for(int i = 0; i < n - 1; i++){
        int least = i;
        for(int j = i + 1; j < n; j++)
            if(list[j] < list[least]) least = i;
        SWAP(list[i], list[least], temp);
    }
}

int main(int argc, char* argv[]){
    n = MAX_SIZE;

    srand(time(NULL));
    for(int i = 0; i < n; i++)
        list[i] = rand() % 100;
    
    selectionSort(list, n);
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]);

    printf("\n");

    return 0;
}
