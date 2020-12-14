#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node{
	int key;
	Node* left;
	Node* right;
};

Node* createNode(int x){
	Node* p = new Node;
	p->key = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void NLR(Node* root){
	if (root != NULL){
		cout << root->key << " ";
		NLR(root->left);
		NLR(root->right);
	}
}

void LNR(Node* root){
	if (root != NULL){
		LNR(root->left);
		cout << root->key << " ";
		LNR(root->right);
	}
}

void LRN(Node* root){
	if (root != NULL){
		LRN(root->left);
		LRN(root->right);
		cout << root->key << " ";
	}
}

void levelOrder(Node* root){
	if (root == NULL)
		return;
	queue<Node*> q;
	q.push(root);
	while (q.size() != 0){
		Node* p = q.front();
		cout << p->key << " ";
		q.pop();
		if (p->left != NULL)
			q.push(p->left);
		if (p->right != NULL)
			q.push(p->right);
	}
}

Node* search(Node* root, int x){
	if (root == NULL)
		return NULL;
	if (root->key == x)
		return root;
	if (root->key > x)
		return search(root->left, x);
	return search(root->right, x);
}

void insert(Node*& root, int x){
	if (root == NULL){
		Node* p = createNode(x);
		root = p;
	}
	else{
		if (root->key > x)
			insert(root->left, x);
		else
			insert(root->right, x);
	}
}

/*void insert2(Node*& root, int x){
	if (root == NULL){
		Node* p = createNode(x);
		root = p;
	}
	else{
		if (root->key <= x)
			insert2(root->left, x);
		else
			insert2(root->right, x);
	}
}*/

void del(Node*& root, Node*& q){
	while (root->right)
		root = root->right;
	q->key = root->key;
	q = root;
	root = root->left; // cap nhat lai de chuong trinh khong bi loi
}

void remove(Node*& root, int x){
	if (root != NULL){
		if (root->key > x)
			remove(root->left, x);
		else if (root->key < x)
			remove(root->right, x);
		else{
			Node* q = root;
			if (root->left == NULL)
				root = q->right;
			else if (root->right == NULL)
				root = q->left;
			else
				del(root->left, q);
			delete q;
		}
	}
}

Node* createTree(int a[], int n){
	Node* root = NULL;
	for (int i = 0; i < n; i++)
		insert(root, a[i]);
	return root;
}

void removeTree(Node*& root){
	if (root != NULL){
		removeTree(root->left);
		removeTree(root->right);
		delete root;
	}
}

int height(Node* root){
	if (root == NULL)
		return 0;
	return 1 + max(height(root->left), height(root->right));
}

int countNode(Node* root){
	if (root == NULL)
		return 0;
	int left = countNode(root->left);
	int right = countNode(root->right);
	return 1 + left + right;
}

int sumNode(Node* root){
	if (root == NULL)
		return 0;
	int left = sumNode(root->left);
	int right = sumNode(root->right);
	return root->key + left + right;
}

int heightNode(Node* root, int value){
	if (root == NULL)
		return -1;
	Node* p = search(root, value);
	if (p == NULL)
		return -1;
	return height(p);
}

int level(Node* root, Node* p){
	int heightOfTree = height(root);
	int distance = 0;
	while (root){
		if (root->key > p->key)
			root = root->left;
		else if (root->key < p->key)	
			root = root->right;
		else
			break;
		distance++;
	}
	return heightOfTree - distance;
}

int countLeaf(Node* root){
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	int left = countLeaf(root->left);
	int right = countLeaf(root->right);
	return left + right;
}

int countLess(Node* root, int x){
	if (root == NULL)
		return 0;
	int left = countLess(root->left, x);
	int right = countLess(root->right, x);
	return (root->key < x ? 1 : 0) + left + right;
}

int countGreater(Node* root, int x){
	if (root == NULL)
		return 0;
	int left = countLess(root->left, x);
	int right = countLess(root->right, x);
	return (root->key > x ? 1 : 0) + left + right;
}

int getMax(Node* root){
	while (root->right != NULL)
		root = root->right;
	return root->key;
}

int getMin(Node* root){
	while (root->left != NULL)
		root = root->left;
	return root->key;
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

bool isFullBST(Node* root){
	if (root == NULL)
		return true;
	if (!isBST(root))
		return false;
	if (root->left == NULL && root->right != NULL)
		return false;
	if (root->left != NULL && root->right == NULL)
		return false;
	if (root->left != NULL && root->right != NULL)
		return (isFullBST(root->left) && isFullBST(root->right));
	return true;
}


int main(){
	Node* root = NULL;
	insert(root, 3);
	root->left = createNode(2);
	root->right = createNode(5);
	root->left->left = createNode(1);
	root->left->right = createNode(4);
	cout << isBST(root) << endl;
	levelOrder(root);
	removeTree(root);
	return 0;
}
