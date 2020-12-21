#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
};

void init(Node*& root) {
	root = NULL;
}

Node* createNode(int x) {
	Node* p = new Node;
	p->key = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

/*int calcHeight(Node* root) {
	if (root == NULL)
		return 0;
	return 1 + max(calcHeight(root->left), calcHeight(root->right));
}

// chen node vao cay nhi phan
void insert(Node*& root, int x) {
	if (root == NULL) {
		Node* p = createNode(x);
		root = p;
	}
	else {
		if (calcHeight(root->left) <= calcHeight(root->right))
			insert(root->left, x);
		else
			insert(root->right, x);
	}
}

void levelOrder(Node* root) {
	queue<Node*> q;
	q.push(root);
	while (q.size() != 0) {
		Node* temp = q.front();
		cout << temp->key << " ";
		q.pop();
		if (temp->left != NULL)
			q.push(temp->left);
		if (temp->right != NULL)
			q.push(temp->right);
	}
	cout << endl;
}

// xoa node trong cay nhi phan
void removeNode(Node*& root, int x) {
	if (root != NULL) {
		if (root->key != x) {
			removeNode(root->left, x);
			removeNode(root->right, x);
		}
		else {
			Node* q = NULL; // con tro luu node truoc node se xoa
			Node* p = root; // con tro the mang
			int d = 0; // bien vi tri, neu d = 0 tuc la leaf, d = 1 se tro ve ben trai, d = -1 se tro ve ben phai
			while (p->left != NULL || p->right != NULL) {
				q = p; // cap nhat node truoc node se xoa
				if (calcHeight(p->left) >= calcHeight(p->right)) {
					swap(p->key, p->left->key);
					p = p->left; // cap nhat node the mang
					d = 1; // cap nhap vi tri
				}
				else {
					swap(p->key, p->right->key);
					p = p->right; // cap nhat node the mang
					d = -1; // cap nhap vi tri
				}
			}
			delete p;
			if (d == 1)
				q->left = NULL;
			else if (d == -1)
				q->right = NULL;
			else
				root = NULL;
		}
	}
}

void removeAll(Node*& root) {
	if (root != NULL) {
		removeAll(root->left);
		removeAll(root->right);
		delete root;
	}
}

int main() {
	Node* root;
	init(root);
	for (int i = 1; i <= 8; i++)
		insert(root, i);
	levelOrder(root);
	removeNode(root, 1);
	levelOrder(root);
	removeAll(root);
	return 0;
}*/

void levelOrder(Node* root) {
	queue<Node*> q;
	q.push(root);
	while (q.size() != 0) {
		Node* temp = q.front();
		cout << temp->key << " ";
		q.pop();
		if (temp->left != NULL)
			q.push(temp->left);
		if (temp->right != NULL)
			q.push(temp->right);
	}
	cout << endl;
}

void removeAll(Node*& root) {
	if (root != NULL) {
		removeAll(root->left);
		removeAll(root->right);
		delete root;
	}
}

void insert(Node*& root, int x){
	Node* k = createNode(x);
	if (root == NULL)
		root = k;
	else{
		Node* p = root; 
		Node* q = NULL; // con tro giu vi tri truoc node p
		int d = 0; // bien dung de xac dinh huong them node vao
		while (p != NULL){
			q = p;
			if (p->key > x){
				p = p->left;
				d = -1;
			}
			else{
				p = p->right;
				d = 1;
			}
		}
		if (d == -1)
			q->left = k;
		else
			q->right = k;
	}
}

void removeNode(Node*& root, int x){
	if (root != NULL){
		Node* q = root; // con tro the mang de xoa
		Node* p = NULL; // con tro truoc node the mang
		int d = 0; // bien vi tri them vao
		while (q->key != x){
			p = q;
			if (q->key > x){
				q = q->left;
				d = -1;
			}
			else{
				q = q->right;
				d = 1;
			}
		}
		// truong hop node can xoa la la hoac chi co mot con
		if (q->left == NULL && d == 1) 
			p->right = q->right;
		else if (q->left == NULL && d == -1)
			p->left = q->right;
		else if (q->right == NULL && d == 1)
			p->right = q->left;
		else if (q->right == NULL && d == -1)
			p->left = q->left;
		else if (q->right != NULL && q->left != NULL){
			Node* k = q->left;
			p = q;
			d = -1;
			while (k->right != NULL){
				p = k;
				k = k->right;
				d = 1;
			}
			q->key = k->key;
			q = k;
			if (d == -1)
				p->left = NULL;
			else
				p->right = NULL;
		}
		delete q;
	}
}

int main(){
	Node* root;
	init(root);
	insert(root, -1);
	insert(root, 22);
	insert(root, 2);
	insert(root, 5);
	insert(root, 1);
	insert(root, 4);
	insert(root, 10);
	insert(root, 14);
	levelOrder(root);
	removeNode(root, 7);
	levelOrder(root);
	removeAll(root);
	return 0;
}
