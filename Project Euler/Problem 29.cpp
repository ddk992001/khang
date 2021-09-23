// DISTINCT POWERS

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string add(string a, string b) {
	string res = "";
	int overflow = 0;
	if (a.size() != b.size()) {
		int size = a.size() - b.size();
		for (int i = 0; i < size; i++)
			b = '0' + b;
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		int temp = int(a[i]) + int(b[i]) + overflow - 96;
		res = to_string(temp % 10) + res;
		overflow = temp / 10;
	}
	if (overflow != 0)
		res = to_string(overflow) + res;
	return res;
}

string mul(string a, int b){
	string res = a;
	for (int i = 2; i <= b; i++)
		res = add(res, a);
	return res;
}

void checkVector(vector<string>& res, string ans){
	bool check = false;
	for (int i = 0; i < res.size(); i++){
		if (res[i] == ans){
			check = true;
			break;
		}
	}
	if (!check)
		res.push_back(ans);
}

int solve(int minA, int maxA, int minB, int maxB){
	vector<string> res;
	for (int i = minA; i <= maxA; i++){
		string ans = to_string(i);
		int count = 2;
		while (count <= minB){
			ans = mul(ans, i);
			count++;
		}
		for (int j = minB+1; j <= maxB; j++){
			checkVector(res, ans);
			ans = mul(ans, i);
		}
		checkVector(res, ans);
	}
	return res.size();
}

int main() {
	cout << "Result: " << solve(2, 100, 2, 100); 
	return 0;
}