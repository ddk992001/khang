// FACTORIAL DIGIT SUM

#include <iostream>
#include <vector>
#include <string>

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

int solve(int n){
	int res = 0;
	string ans = "1";
	for (int i = 1; i <= n; i++){
		string temp = ans;
		for (int j = 2; j <= i; j++){
			ans = add(ans, temp);
		}
		while (ans[ans.size()-1] == '0')
			ans.erase(ans.size()-1);
	}	
	for (int i = 0; i < ans.size(); i++)
		res += int(ans[i])-48;
	return res;
}

int main() {
	cout << "Result: " << solve(100);
	return 0;
}