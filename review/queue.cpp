#include <stdio.h>
#include <queue>
using namespace std;

void showMenu(){
	printf("\n1.PUSH\n");
	printf("2.POP\n");
	printf("3.QUIT\n");
	printf("->");
}

void pushFunc(queue<int>& queue_ref){
	printf("INPUT: ");
	int input = 0;
	scanf("%d", &input);
	queue_ref.push(input);
	printf("%d PUSHED!\n", queue_ref.back());
}

void popFunc(queue<int>& queue_ref){
	if(!queue_ref.empty()){
		printf("%d POPPED!\n", queue_ref.front());
		queue_ref.pop();
	}
	else{
		printf("QUEUE IS EMPTY\n");
	}
}

int main(int argc, char* argv[]){
	int menu = 0;
	int flag = 1;

	queue<int> myqueue;
	queue<int> &queue_ref = myqueue;
	
	while(flag){
		showMenu();
		scanf("%d", &menu);
		switch(menu){
			case 1: 
				pushFunc(queue_ref);
				break;
			case 2:
				popFunc(queue_ref);
				break;
			case 3:
				flag = 0;
				break;
		}
	}

	return 0;
}
