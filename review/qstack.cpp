#include <stdio.h>
#include <queue>
using namespace std;

void showMenu(){
	printf("\n1.PUSH\n");
	printf("2.POP\n");
	printf("3.QUIT\n");
	printf("->");
}

void pushFunc(queue<int> &qstack_ref){
	int input = 0;
	printf("INPUT:");
	scanf("%d", &input);
	qstack_ref.push(input);
	printf("%d PUSHED!\n", qstack_ref.back());
}

void popFunc(queue<int> &qstack_ref){
	if(qstack_ref.empty()){
		printf("STACK EMPTY!\n");
		return;
	}
	for(int i = 0; i < qstack_ref.size()-1; i++){
		int tmp = qstack_ref.front();
		qstack_ref.pop();
		qstack_ref.push(tmp);
	}
	printf("%d POPPED!\n", qstack_ref.front());
	qstack_ref.pop();
}

int main(int argc, char* argv[]){
	int flag = 1;
	int menu = -1;

	queue<int> qstack;
	queue<int> &qstack_ref = qstack;

	while(flag){
		showMenu();
		scanf("%d", &menu);
		switch(menu){
			case 1:
				pushFunc(qstack_ref);
				break;
			case 2:
				popFunc(qstack_ref);
				break;
			case 3:
				flag = 0;
				break;
		}
	}

	return 0;
}
