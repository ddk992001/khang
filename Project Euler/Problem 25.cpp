// 1000-DIGIT FIBONACCI NUMBER

#include <iostream>
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
	if (n == 1)
		return 1;
	string f1 = "1";
	string f2 = "1";
	int index = 2;
	string res = "";
	while (res.size() != n){
		res = add(f2, f1);
		f1 = f2;
		f2 = res;
		index++;
	}
	return index;
}

int main() {
	cout << "Result: " << solve(1000); 
	return 0;
}