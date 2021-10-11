#include <stdio.h>
#include <stdlib.h>

void printMenu(){
	printf("\n1.PUSH\n");
	printf("2.POP\n");
	printf("3.QUIT\n");
	printf("->");
}

int main(int argc, char* argv[]){

	int flag = 1;
	int menu = -1;

	while(flag){
		scanf("%d", &menu);
		switch(menu){
			case 1:
				push();
				break;
			case 2:
				pop();
				break;
			case 3:
				flag = 0;
				break;
		}
	}

	return 0
}
