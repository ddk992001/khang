// DOUBLE-BASE PALINDROMES

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isPalindrome(string num){
	for (int i = 0; i < num.size()/2; i++){
		if (num[i] != num[num.size()-1-i])
			return false;
	}
	return true;
}

string findBinary(int n){
	string res = "";
	while (n != 0){
		res = char(n % 2 + 48) + res;
		n /= 2;
	}
	return res;
}

int solve(int n){
	vector<int> num;
	int res = 0;
	for (int i = 1; i < n; i++){
		string binary = findBinary(i);
		string temp = to_string(i);
		if (isPalindrome(temp) && isPalindrome(binary))
			num.push_back(i);
	}
	for (int i = 0; i < num.size(); i++)
		res += num[i];
	return res;
}

int main() {
	cout << "Result: " << solve(1000000); 
	return 0;
}