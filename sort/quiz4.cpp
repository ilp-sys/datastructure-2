#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <sys/time.h>

#define SWAP(x, y, t) ((t)=(x),(x)=(y),(y)=(t))
using namespace std;

float timeDiff(struct timeval * start, struct timeval *end){
    //double elapsed =  ((doubl)(end->tv_sec - start->tv_sec) + (double)(end->tv_usec - start->tv_usec)/1000000);
    float elapsed = (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
    return elapsed;
}

void printer(int array[], int n){
    if(n <= 100)
        for(int i = 0; i < n; i++)
            printf("%d ", array[i]);
}

void insertionSort(int array[], int n){
    int i, j, key;
    for(i = 1; i < n; i++){
        key = array[i];
        for(j = i-1; j >= 0 && array[j]>key; j--)
            array[j+1] = array[j];
        array[j+1] = key;
    }
    printer(array, n);
}

void selectionSort(int array[], int n){
    int temp = 0;
    for(int i = 0; i < n-1; i++){
        int least = i;
        for(int j = i+1; j < n; j++)
            if(array[j] < array[least]) least = j;
        SWAP(array[i], array[least], temp);
    }
    printer(array, n);
}

void bubbleSort(int array[], int n){
    int temp = 0;
    for(int i = n-1; i > 0; i--){
        for(int j = 0; j < i; j++)
            if(array[j] > array[j+1])
                SWAP(array[j], array[j+1], temp);
    }
    printer(array, n);
}

int main(int argc, char* argv[]){
    //배열 개수 입력받기
    int n = 0;
    printf("ipnut n >> ");
    scanf("%d", &n);

    //랜덤 배열 생성
    srand(time(NULL));
    int input[n];
    for(int i = 0; i < n; i++)
        input[i] = rand()%101+10;

    //입력받은 개수가 100보다 작으면 출력
    if(n <= 100){
        printf("random arr to sort: ");
        for(int i = 0; i < n; i++)
            printf("%d ", input[i]);
    }
    printf("\n\n");

    //정렬 알고리즘 비교 - insertion
    struct timeval start, end;
    int *input1 = (int*)malloc(sizeof(int)*n);
    memcpy(input1, input, sizeof(input));
    gettimeofday(&start, NULL);
    insertionSort(input1, n);
    gettimeofday(&end, NULL);
    printf("\ninsertion sort time cost: %.8f\n\n", timeDiff(&start, &end));

    //정렬 알고리즘 비교 - selection
    int *input2 = (int*)malloc(sizeof(int)*n);
    memcpy(input2, input, sizeof(input));
    gettimeofday(&start, NULL);
    selectionSort(input2, n);
    gettimeofday(&end, NULL);
    printf("\nselection sort time cost: %.8f\n\n", timeDiff(&start, &end));

    //정렬 알고리즘 비교 - bubble
    int *input3 = (int*)malloc(sizeof(int)*n);
    memcpy(input3, input, sizeof(input));
    gettimeofday(&start, NULL);
    bubbleSort(input3, n);
    gettimeofday(&end, NULL);
    printf("\nbubble sort time cost: %.8f\n\n", timeDiff(&start, &end));

    //정렬 알고리즘 비교 - stl sort
    gettimeofday(&start, NULL);
    sort(input, input+n);
    gettimeofday(&end, NULL);
    printer(input, n);
    printf("\nstl sort time cost: %.8f\n\n", timeDiff(&start, &end));

    return 0;
}
