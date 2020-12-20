#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

void insert(Node*& root, int x) {
	if (root == NULL) {
		Node* p = createNode(x);
		root = p;
	}
	else {
		if (root->key > x)
			insert(root->left, x);
		else
			insert(root->right, x);
	}
}

Node* search(Node* root, int a) {
	if (root == NULL)
		return NULL;
	while (root != NULL) {
		if (root->key > a)
			root = root->left;
		else if (root->key < a)
			root = root->right;
		else
			return root;
	}
	return NULL;
}

int count(Node* root, int b) {
	if (root == NULL)
		return 0;
	int left = count(root->left, b);
	int right = count(root->right, b);
	return (root->key % b == 0 ? 1 : 0) + left + right;
}

int getLevel(Node* root, Node* p) {
	if (root == NULL)
		return 0;
	int level = 1;
	while (root->key != p->key) {
		if (root->key > p->key)
			root = root->left;
		else
			root = root->right;
		level++;
	}
	return level;
}

int findValue(Node* root, int k) {
	if (root == NULL)
		return -1;
	queue<Node*> q;
	q.push(root);
	int max = 0;
	while (q.size() != 0) {
		Node* temp = q.front();
		q.pop();
		if (getLevel(root, temp) == k && temp->left != NULL && temp->right != NULL && temp->key > max)
			max = temp->key;
		if (temp->left != NULL)
			q.push(temp->left);
		if (temp->right != NULL)
			q.push(temp->right);
	}
	return max;
}

int getMax(Node* root) {
	while (root->right != NULL)
		root = root->right;
	return root->key;
}

void removeNode(Node*& root, int x) {
	if (root == NULL)
		return;
	if (root->key > x)
		removeNode(root->left, x);
	else if (root->key < x)
		removeNode(root->right, x);
	else {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		else if (root->left == NULL) {
			Node* p = root;
			root = root->right;
			delete p;
		}
		else if (root->right == NULL) {
			Node* p = root;
			root = root->left;
			delete p;
		}
		else {
			int value = getMax(root->left);
			root->key = value;
			removeNode(root->left, value);
		}
	}
}

void LRN(Node* root) {
	if (root != NULL) {
		LRN(root->left);
		LRN(root->right);
		cout << root->key << " ";
	}
}

void removeAll(Node*& root) {
	if (root != NULL) {
		removeAll(root->left);
		removeAll(root->right);
		delete root;
	}
}

vector<string> split(string haystack, string separator) {
	vector<string> tokens;
	int start = 0;
	while (true) {
		size_t pos = haystack.find(separator, start);
		if (pos != string::npos) {
			string token = haystack.substr(start, pos - start);
			tokens.push_back(token);
			start = pos + separator.size();
		}
		else {
			string token = haystack.substr(start, haystack.size() - start);
			tokens.push_back(token);
			break;
		}
	}
	return tokens;
}

void readFile(string path, vector<int>& num, int& a, int& b, int& k) {
	ifstream fin;
	fin.open(path);
	int count = 1;
	while (count <= 3) {
		string line;
		getline(fin, line);
		vector<string> tokens = split(line, " ");
		if (count == 1) {
			for (int i = 0; i < tokens.size() ; i++) {
				if (i != tokens.size() - 1)
					num.push_back(stoi(tokens[i]));
				else {
					string temp = tokens[i].substr(0, tokens[i].size() - 1);
					num.push_back(stoi(tokens[i]));
				}
			}
		}
		else if (count == 2) {
			a = stoi(tokens[0]);
			b = stoi(tokens[1]);
		}
		else
			k = stoi(tokens[0]);
		count++;
	}
	fin.close();
}

int main() {
	vector<int> num;
	int a, b, k;
	Node* root;
	init(root);
	readFile("input.txt", num, a, b, k);
	for (int i = 0; i < num.size(); i++)
		insert(root, num[i]);
	LRN(root);
	cout << endl;
	Node* p = search(root, a);
	cout << count(p->left, b) + count(p->right, b) << endl;
	removeNode(root, findValue(root, k));
	LRN(root);
	removeAll(root);
}