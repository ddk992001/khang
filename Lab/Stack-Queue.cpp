#include <iostream>

using namespace std;

struct Node{
	int key;
	Node* next;
};

struct Stack{
	Node* head;
};

struct Queue{
	Node* head;
	Node* tail;
};

Node* createNode(int data){
	Node* p = new Node;
	p->key = data;
	p->next = NULL;
	return p;
}

Stack* initializeStack(Node* p){
	Stack* s = new Stack;
	s->head = p;
	return s;
}

void push(Stack*& s, int data){
	Node* p = createNode(data);
	if (s->head == NULL)
		s->head = p;
	else{
		p->next = s->head;
		s->head = p;
	}
}

int pop(Stack*& s){
	if (s->head == NULL)
		return -1;
	int data = s->head->key;
	Node* q = s->head;
	s->head = s->head->next;
	delete q;
	return data;
}

int countElements(Stack* s){
	int count = 0;
	for (Node* i = s->head; i != NULL; i = i->next)
		count++;
	return count;
}

bool isEmpty(Stack* s){
	if (s->head == NULL)
		return true;
	return false;
}

Queue* initializeQueue(Node* p){
	Queue* q = new Queue;
	q->head = q->tail = p;
	return q;
}

void enqueue(Queue*& q, int data){
	Node* p = createNode(data);
	if (q->head == NULL)
		q->head = q->tail = p;
	else{
		q->tail->next = p;
		q->tail = p;
	}
}

int dequeue(Queue*& q){
	if (q->head == NULL)
		return -1;
	int data = q->head->data;
	Node* p = q->head;
	q->head = q->head->next;
	delete p;
	return data;
}

int countElements(Queue* q){
	int count = 0;
	for (Node* i = q->head; i != NULL; i = i->next)
		count++;
	return count;
}

bool isEmpty(Queue* q){
	if (q->head == NULL)
		return true;
	return false;
}

int main(){
	
}
