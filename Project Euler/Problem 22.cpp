// NAMES SCORES

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

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

void sort(vector<string>& names){
	for (int i = 0; i < names.size()-1; i++){
		for (int j = i+1; j < names.size(); j++){
			if (strcmp(names[i].c_str(), names[j].c_str()) > 0)
				swap(names[i], names[j]);
		}
	}
}

int calcValue(string name){
	int res = 0;
	for (int i = 1; i < name.size()-1; i++)
		res += int(name[i])-64;
	return res;
}

long long solve(char* path){
	long long res = 0;
	ifstream fin;
	fin.open(path);
	vector<string> names;
	string line = "";
	getline(fin, line);
	names = split(line, ",");
	sort(names);
	for (int i = 0; i < names.size(); i++){
		int value = calcValue(names[i]);
		res += (long long)(value * (i+1));
	}
	fin.close();
	return res;
}

int main() {
	char* path = "C:\\Users\\DELL\\Desktop\\names.txt";
	cout << "Result: " << solve(path);
	return 0;
}