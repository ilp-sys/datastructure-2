#include <stdio.h>
#include <stack>
#include <queue>
using namespace std;

int main(int argc, char* argv[]){
	stack<int> s;
	queue<int> q;

	for(int i = 0; i < 10; i ++){
		s.push(i);
		q.push(i);
	}

	printf("Stack..");
	for(int i = 0; i < 10; i ++){
		printf("%d", s.top());
		s.pop();
	}
	printf("\n");

	printf("Queue..");
	for(int i = 0; i < 10; i ++){
		printf("%d", q.front());
		q.pop();
	}
	printf("\n");

	return 0;
}
