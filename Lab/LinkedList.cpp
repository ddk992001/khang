#include <iostream>

using namespace std;

struct Node{
	int data;
	Node* next;
};

struct List{
	Node* head;
	Node* tail;
};

Node* createNode(int data){
	Node* p = new Node;
	p->data = data;
	p->next = NULL;
	return p;
}

List* createList(Node* p_node){
	List* list = new List;
	list->head = list->tail = p_node;
	return list;
}

void addHead(List* &L, int data){
	Node* p = createNode(data);
	if (L->head == NULL)
		L->head = L->tail = p;
	else{
		p->next = L->head;
		L->head = p;
	}
}

void addTail(List* &L, int data){
	Node* p = createNode(data);
	if (L->head == NULL)
		L->head = L->tail = p;
	else{
		L->tail->next = p;
		L->tail = p;
	}
}

void removeHead(List* &L){
	if (L->head == NULL)
		return;
	Node* p = L->head;
	L->head = L->head->next;
	delete p;
}

void removeTail(List* &L){
	if (L->head == NULL)
		return;
	for (Node* i = L->head; i != NULL; i = i->next){
		if (i->next == L->tail){
			Node* p = L->tail;
			L->tail = i;
			L->tail->next = NULL;
			delete p;
			break;
		}
	}
}

void removeAll(List* &L){
	while (L->head != NULL)
		removeHead(L);
}

void printList(List* L){
	for (Node* i = L->head; i != NULL; i = i->next)
		cout << i->data << " ";
}

int countElements(List* L){
	int count = 0;
	for (Node* i = L->head; i != NULL; i = i->next)
		count++;
	return count;
}

List* reverseList(List* L){
	List* list = new List;
	list->head = NULL;
	list->tail = NULL;
	for (Node* i = L->head; i != NULL; i = i->next)
		addHead(list, i->data);
	return list;
}

void RemoveDuplicate(List* &L){
	for (Node* i = L->head; i != NULL; i = i->next){
		Node* temp = i;
		for (Node* j = i->next; j != NULL; j = j->next){
			if (i->data == j->data){
				temp->next = j->next;
				Node* q = j;
				j = temp;
				delete q;
				if (j == NULL)
					break;
			}
			else
				temp = j;
		}
	}
}

void RemoveElement(List* &L, int key){
	while (L->head != NULL && L->head->data == key)
		removeHead(L);
	while (L->tail != NULL && L->tail->data == key)
		removeTail(L);
	if (L->head != NULL){
		Node* q = L->head;
		for (Node* i = L->head->next; i != NULL; i = i->next){
			if (i->data == key){
				q->next = i->next;
				Node* temp = i;
				i = q;
				delete temp;
			}
			else
				q = i;
		}
	}
}

int main(){
	Node* p = createNode(3);
	List* l = createList(p);
	addHead(l, 3);
	addTail(l, 2);
	addTail(l, 2);
	addTail(l, 3);
	addTail(l, 3);
	RemoveElement(l, 2);
	printList(l);
	removeAll(l);
	delete l;
	return 0;
}
