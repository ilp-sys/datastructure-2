#include <stdio.h>
#include <stdlib.h>

int rcsvSum(int n, int m){
	if(n == m){//stop when n reaches to m
		printf("%d\n", n);
		return m;
	}
	printf("%d ", n);
	return n + rcsvSum(n+1, m);
}

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Wrong Input...\n");
		printf("Usage)./ntom.out n m\n");
		return -1;
	}

	long int argv1 = strtol(argv[1], NULL, 10);//convert string to long int
	long int argv2 = strtol(argv[2], NULL, 10);

	int result = rcsvSum(argv1, argv2);
	printf("Sum = %d\n", result);

	return 0;
}
