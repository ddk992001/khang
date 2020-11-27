/*#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

void initialize(Company& p) {
	p.name = "";
}

vector<string> split(string haystack, string separator) {
	vector<string> tokens;
	int start = 0;
	while (true) {
		size_t pos = haystack.find(separator, start);
		if (pos != string::npos) {
			string temp = haystack.substr(start, pos - start);
			tokens.push_back(temp);
			start = pos + separator.size();
		}
		else {
			string temp = haystack.substr(start, haystack.size() - start);
			tokens.push_back(temp);
			break;
		}
	}
	return tokens;
}

vector<Company> readCompanyList(string file_name) {
	ifstream fin;
	fin.open(file_name.c_str());
	vector<Company> company;
	string line;
	getline(fin, line);
	while (!fin.eof()) {
		getline(fin, line);
		if (line.size() == 0)
			break;
		vector<string> tokens = split(line, "|");
		Company temp;
		temp.name = tokens[0];
		temp.profit_tax = tokens[1];
		temp.address = tokens[2];
		company.push_back(temp);
	}
	fin.close();
	return company;
}

long long hashString(string company_name) {
	long long value = 0;
	long long p = 1;
	string temp;
	if (company_name.size() <= 20)
		temp = company_name;
	else
		temp = company_name.substr(company_name.size() - 21, 20);
	for (int i = 0; i < temp.size(); i++) {
		value += int(temp[i]) * (p % 1000000009);
		p *= 31;
		p %= 1000000009;
		value %= 1000000009;
	}
	return value % 1000000009;
}

// linear probing
Company* createHashTable(vector<Company> company_list) {
	Company* company = new Company[2000];
	for (int i = 0; i < 2000; i++)
		initialize(company[i]);
	for (int i = 0; i < company_list.size(); i++) {
		long long value = hashString(company_list[i].name) % 2000;
		while (company[value].name.size() != 0) {
			value++;
			value %= 2000;
		}
		company[value] = company_list[i];
	}
	return company;
}

void insert(Company* hash_table, Company company) {
	long long value = hashString(company.name) % 2000;;
	while (hash_table[value].name.size() != 0) {
		value++;
		value %= 2000;
	}
	hash_table[value] = company;
}

Company* search(Company* hash_table, string company_name) {
	long long value = hashString(company_name) % 2000;
	while (hash_table[value].name != company_name && hash_table[value].name.size() != 0) {
		value++;
		value %= 2000;
	}
	if (hash_table[value].name == company_name)
		return &hash_table[value];
	return NULL;
}

int main() {
	vector<Company> company_list = readCompanyList("E:\\HK1-Year 2\\DSAA\\Lab 3\\MST.txt");
	Company* company = createHashTable(company_list);
	Company p;
	p.name = "Cong ty TNHH ABC XYZ";
	p.address = "227 Nguyen Van Cu, Q5, TPHCM";
	p.profit_tax = "0123456789";
	insert(company, p);
	Company* pointer = search(company, p.name);
	if (pointer == NULL)
		cout << "No";
	else
		cout << "YES";
	delete[] company;
	return 0;
}*/
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

struct Node {
	Company key;
	Node* next;
};

struct List {
	Node* head;
	Node* tail;
};

vector<string> split(string haystack, string separator) {
	vector<string> tokens;
	int start = 0;
	while (true) {
		size_t pos = haystack.find(separator, start);
		if (pos != string::npos) {
			string temp = haystack.substr(start, pos - start);
			tokens.push_back(temp);
			start = pos + separator.size();
		}
		else {
			string temp = haystack.substr(start, haystack.size() - start);
			tokens.push_back(temp);
			break;
		}
	}
	return tokens;
}

vector<Company> readCompanyList(string file_name) {
	ifstream fin;
	fin.open(file_name.c_str());
	vector<Company> company;
	string line;
	getline(fin, line);
	while (!fin.eof()) {
		getline(fin, line);
		if (line.size() == 0)
			break;
		vector<string> tokens = split(line, "|");
		Company temp;
		temp.name = tokens[0];
		temp.profit_tax = tokens[1];
		temp.address = tokens[2];
		company.push_back(temp);
	}
	fin.close();
	return company;
}

long long hashString(string company_name) {
	long long value = 0;
	long long p = 1;
	string temp;
	if (company_name.size() <= 20)
		temp = company_name;
	else
		temp = company_name.substr(company_name.size() - 21, 20);
	for (int i = 0; i < temp.size(); i++) {
		value += int(temp[i]) * (p % 1000000009);
		p *= 31;
		p %= 1000000009;
		value %= 1000000009;
	}
	return value % 1000000009;
}

Node* createNode(Company p) {
	Node* k = new Node;
	k->key = p;
	k->next = NULL;
	return k;
}

void addTail(List& l, Company p) {
	Node* k = createNode(p);
	if (l.head == NULL)
		l.head = l.tail = k;
	else {
		l.tail->next = k;
		l.tail = k;
	}
}

List* createHashTable(vector<Company> company_list) {
	List* list = new List[2000];
	for (int i = 0; i < 2000; i++)
		list[i].head = list[i].tail = NULL;
	for (int i = 0; i < company_list.size(); i++) {
		long long value = hashString(company_list[i].name) % 2000;
		addTail(list[value], company_list[i]);
	}
	return list;
}

void insert(List* list, Company company) {
	long long value = hashString(company.name) % 2000;
	addTail(list[value], company);
}

Company* search(List* list, string company_name) {
	long long value = hashString(company_name) % 2000;
	for (Node* k = list[value].head; k != NULL; k = k->next) {
		if (k->key.name == company_name)
			return &k->key;
	}
	return NULL;
}

int main() {
	vector<Company> company_list = readCompanyList("E:\\HK1-Year 2\\DSAA\\Lab 3\\MST.txt");
	List* company = createHashTable(company_list);
	for (int i = 0; i < 2000; i++) {
		for (Node* k = company[i].head; k != NULL; k = k->next)
			cout << k->key.name << endl;
	}
	Company p;
	p.name = "Cong ty TNHH ABC XYZ";
	p.address = "227 Nguyen Van Cu, Q5, TPHCM";
	p.profit_tax = "0123456789";
	insert(company, p);
	Company* pointer = search(company, p.name);
	if (pointer == NULL)
		cout << "No";
	else
		cout << "YES";
	delete[] company;
	return 0;
}
// open hashing