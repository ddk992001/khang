#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	int height;
};

Node* createNode(int data) {
	Node* p = new Node;
	p->key = data;
	p->left = NULL;
	p->right = NULL;
	p->height = 1;
	return p;
}

int getHeight(Node* root) {
	if (root == NULL)
		return 0;
	return root->height;
}

// ham quay phai
void rightRotation(Node*& p) {
	Node* q = p->left;
	p->left = q->right;
	q->right = p; // 3 dong tren thuc hien qua trinh quay
	p->height = 1 + max(getHeight(p->left), getHeight(p->right));
	q->height = 1 + max(getHeight(q->left), getHeight(q->right)); // 2 dong tiep theo cap nhat chieu cao 
	p = q; // gan node goc voi gia tri moi
}

// ham quay trai
void leftRotation(Node*& p) {
	Node* q = p->right;
	p->right = q->left;
	q->left = p; // 3 dong tren thuc hien qua trinh quay
	p->height = 1 + max(getHeight(p->left), getHeight(p->right));
	q->height = 1 + max(getHeight(q->left), getHeight(q->right)); // 2 dong tiep theo cap nhat chieu cao 
	p = q; // gan node goc voi gia tri moi
}

void insert(Node*& root, int data) {
	if (root == NULL) {
		Node* p = createNode(data);
		root = p;
	}
	else {
		if (root->key > data)
			insert(root->left, data);
		else if (root->key < data)
			insert(root->right, data);
		else
			return;
	}  // cac buoc tren thuc hien qua trinh chen node vao cay BST nhu thong thuong
	root->height = 1 + max(getHeight(root->left), getHeight(root->right)); // cap nhat lai chieu cao node sau khi chen vao
	if (getHeight(root->left) - getHeight(root->right) > 1) {
		if (getHeight(root->left->left) >= getHeight(root->left->right)) // LL
			rightRotation(root);
		else { // LR
			leftRotation(root->left);
			rightRotation(root);
		}
	}
	else if (getHeight(root->left) - getHeight(root->right) < -1) {
		if (getHeight(root->right->right) >= getHeight(root->right->left)) // RR
			leftRotation(root);
		else { // RL
			rightRotation(root->right);
			leftRotation(root);
		}
	}
}

int getMax(Node* root) {
	while (root->right != NULL)
		root = root->right;
	return root->key;
}

int getMin(Node* root){
	while (root->left != NULL)
		root = root->left;
	return root->key;
}

void remove(Node*& root, int data) {
	if (root == NULL)
		return;
	if (root->key > data)
		remove(root->left, data);
	else if (root->key < data)
		remove(root->right, data);
	else {
		Node* p = root;
		if (p->left == NULL) {
			root = p->right;
			delete p;
		}
		else if (p->right == NULL) {
			root = p->left;
			delete p;
		}
		else {
			int maxValue = getMax(root->left);
			root->key = maxValue;
			remove(root->left, maxValue);
		}
		return;
	}
	root->height = 1 + max(getHeight(root->left), getHeight(root->right)); // cap nhat lai chieu cao node sau khi chen vao
	if (getHeight(root->left) - getHeight(root->right) > 1) {
		if (getHeight(root->left->left) >= getHeight(root->left->right)) // LL
			rightRotation(root);
		else { // LR
			leftRotation(root->left);
			rightRotation(root);
		}
	}
	else if (getHeight(root->left) - getHeight(root->right) < -1) {
		if (getHeight(root->right->right) >= getHeight(root->right->left)) // RR
			leftRotation(root);
		else { // RL
			rightRotation(root->right);
			leftRotation(root);
		}
	}
}

void LNR(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		cout << root->key << " ";
		LNR(root->right);
	}
}

void NLR(Node* root) {
	if (root != NULL) {
		cout << root->key << " ";
		LNR(root->left);
		LNR(root->right);
	}
}

void LRN(Node* root) {
	if (root != NULL) {
		LNR(root->left);
		LNR(root->right);
		cout << root->key << " ";
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
}

void removeAll(Node*& root) {
	if (root != NULL) {
		removeAll(root->left);
		removeAll(root->right);
		delete root;
	}
}

bool isBST(Node* root){
	if (root == NULL)
		return true;
	if (root->left != NULL && getMax(root->left) > root->key)
		return false;
	if (root->right != NULL && getMin(root->right) < root->key)
		return false;
	return isBST(root->left) && isBST(root->right);
}

bool isAVL(Node* root){
	if (root == NULL)
		return true;
	if (!isBST(root))
		return false;
	if (getHeight(root->left) - getHeight(root->right) > 1 || getHeight(root->left) - getHeight(root->right) < -1)
		return false;
	bool left = isAVL(root->left);
	bool right = isAVL(root->right);
	return left && right;
}

int main() {
	//Node* root = NULL;
	/*insert(root, 10);
	insert(root, 5);
	insert(root, 20);
	insert(root, 15);
	insert(root, 30);
	insert(root, 12);
	remove(root, 15);*/
	Node* root = createNode(1); 
    root->left = createNode(2); 
    root->right = createNode(3); 
    root->left->left = createNode(4); 
    root->left->right = createNode(5); 
    root->left->left->left = createNode(8);
	cout << isAVL(root);
	//levelOrder(root);
	removeAll(root);
}
