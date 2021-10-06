// CODED TRIANGLE NUMBERS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

int calcValue(string word){
	int res = 0;
	for (int i = 1; i < word.size()-1; i++)
		res += int(word[i]) - 64;
	return res;
}

bool isTriangleNumber(int num){
	int i = 1;
	while (true){
		if (i*(i+1)/2 == num)
			return true;
		if (i*(i+1)/2 > num)
			return false;
		i++;
	}
}

int solve(char* path){
	int count = 0;
	ifstream fin;
	fin.open(path);
	vector<string> words;
	string line = "";
	getline(fin, line);
	words = split(line, ",");
	for (int i = 0; i < words.size(); i++){
		int value = calcValue(words[i]);
		if (isTriangleNumber(value))
			count++;
	}
	return count;
}

int main() {
	char* path = "C:\\Users\\DELL\\Desktop\\words.txt";
	cout << "Result: " << solve(path); 
	return 0;
}