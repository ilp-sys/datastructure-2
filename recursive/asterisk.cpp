#include <stdio.h>

void rcsvAsterisk(int n){
	if(n==0){
		printf("\n");
		return;
	}
	printf("*");
	rcsvAsterisk(n-1);
}

int main(int argc, char* argv[]){
	rcsvAsterisk(5);
	return 0;
}
