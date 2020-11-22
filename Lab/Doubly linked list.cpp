#include <iostream>

using namespace std;

struct Node{
	int key;
	Node* next;
	Node* prev;
};

struct List{
	Node* head;
	Node* tail;
};

Node* createNode(int x){
	Node* p = new Node;
	p->key = x;
	p->next = NULL;
	p->prev = NULL;
	return p;
}

void initialize(List& l, int x){
	Node* p = createNode(x);
	l.head = l.tail = p;
}

void addHead(List& l, int x){
	Node* p = createNode(x);
	if (l.head == NULL)
		l.head = l.tail = p;
	else{
		p->next = l.head;
		l.head->prev = p;
		l.head = p;
	}
}

int countElements(List l){
	int count = 0;
	for (Node* i = l.head; i != NULL; i = i->next)
		count++;
	return count;
}

void addBeforeNode(List& l, int x, int pos){
	int count = 0;
	if (pos == 0)
		addHead(l, x);
	else{
		for (Node* i = l.head; i != NULL; i = i->next){
			if (pos == count){
				Node* p = createNode(x);
				p->next = i;
				p->prev = i->prev;
				i->prev->next = p;
				i->prev = p;
				break;
			}
			count++;
		}
	}
}

void addTail(List& l, int x){
	Node* p = createNode(x);
	if (l.head == NULL)
		l.head = l.tail = p;
	else{
		l.tail->next = p;
		p->prev = l.tail;
		l.tail = p;
	}
}

void addAfterNode(List& l, int x, int pos){
	if (pos == countElements(l)-1)
		addTail(l, x);
	else{
		addBeforeNode(l, x, pos + 1);
	}
}

void removeHead(List& l){
	if (l.head != NULL){
		Node* p = l.head;
		l.head = l.head->next;
		delete p;
		if (l.head != NULL)
			l.head->prev = NULL;
	}
}

void removeTail(List& l){
	if (l.tail != NULL){
		Node* p = l.tail;
		l.tail = l.tail->prev;
		delete p;
		if (l.tail != NULL)
			l.tail->next = NULL;
	}
}

void removeNode(List& l, int x){
	if (l.head->key == x)
		removeHead(l);
	else{
		for (Node* i = l.head; i != NULL; i = i->next){
			if (i->key == x && i == l.tail){
				removeTail(l);
				break;
			}
			else if (i->key == x){
				i->next->prev = i->prev;
				i->prev->next = i->next;
				delete i;
				break;
			}
		}	
	}
}

void printList(List l){
	for (Node* i = l.head; i != NULL; i = i->next)
		cout << i->key << " ";
	cout << endl;
}

int main(){
	List l;
	initialize(l, 1);
	for (int i = 2; i <= 5; i++)
		addTail(l, i);
	addHead(l, 0);
	addHead(l, -1);
	printList(l);
	removeNode(l, 5);
	printList(l);
	while (l.head != NULL)
		removeHead(l);
	return 0;
}
