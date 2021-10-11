#include <stdio.h>
#include <stack>
using namespace std;

void showMenu(){
	printf("\n1.PUSH\n");
	printf("2.POP\n");
	printf("3.QUIT\n");
	printf("-> ");
}

void casePush(stack<int> &stack_ref){
	int input = 0;
	printf("INPUT: ");
	scanf("%d", &input);
	stack_ref.push(input);
	printf("%d PUSHED!\n", stack_ref.top());
}

void casePop(stack<int> &stack_ref){
	if(!stack_ref.empty()){
		printf("%d POPPED!\n", stack_ref.top());
		stack_ref.pop();
	}
	else{
		printf("STACK IS EMPTY!\n");
	}
}


int main(int argc, char* argv[]){

	int flag = 1;
	int menu = 0;
	stack<int> mystack;
	stack<int> &stack_ref = mystack;

	while(flag){
		showMenu();
		scanf("%d", &menu);
		switch(menu){
			case 1:
				casePush(stack_ref);
				break;
			case 2:
				casePop(stack_ref);
				break;
			case 3:
				flag = 0;
				break;
		}
	}

	return 0;
}
