#include <stdio.h>
#include <stdlib.h>
//노드 및 스택 구조체 선언

typedef struct node{
	int data;
	node* link;
}node;

typedef struct stack{
	int count;
	node* top_node;
}stack;

node* createNode(stack* stack){
	int item = -99;
	printf("INPUT: ");
	scanf("%d", &item);
	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = item;
	new_node->link = stack->top_node;
	return new_node;
}

void push(stack** stack){
	node* new_node = createNode(*stack);
	(*stack)->count++;
	(*stack)->top_node = new_node;
	printf("%d PUSHED!\n", (*stack)->top_node->data);
}

void pop(stack** stack){
	if((*stack)->count <= 0){
		printf("STACK IS EMPTY!\n");
		return;
	}
	node* tmp = (node*)malloc(sizeof(node));
	tmp->data = (*stack)->top_node->data;
	tmp->link = (*stack)->top_node->link;
	(*stack)->top_node = (*stack)->top_node->link;
	(*stack)->count--;
	printf("%d POPPED!\n", tmp->data);
	free(tmp);
}

stack* createStack(){
	stack* newStack = (stack*)malloc(sizeof(stack));
	newStack->count = 0;
	newStack->top_node = NULL;
	return newStack;
}

void printMenu(){
	printf("\n1.PUSH\n");
	printf("2.POP\n");
	printf("3.QUIT\n");
	printf("-> ");
}

int main(int argc, char* argv[]){
	int flag = 1;
	int menu = -1;

	stack* stack = createStack();

	while(flag){
		printMenu();
		scanf("%d", &menu);
		switch(menu){
			case 1:
				push(&stack);
				break;
			case 2:
				pop(&stack);
				break;
			case 3:
				flag = 0;
				break;
		}
	}
	return 0;
}
