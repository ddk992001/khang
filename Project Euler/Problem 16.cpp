// 3 - 5 - 2002

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

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

long long solve(long long n){
	if (n < 4)
		return pow(2, n); 
	long long sum = 0;
	string res = "8";
	for (int i = 4; i <= n; i++)
		res = add(res, res);
	for (int i = 0; i < res.size(); i++)
		sum += int(res[i]) - 48;
	return sum;
}

int main() {
	cout << "Result: " << solve(1000);
	return 0;
}
