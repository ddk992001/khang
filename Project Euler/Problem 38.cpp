// PANDIGITAL MULTIPLES

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

string solve(int n){
	string res = "", cmp = "";
	for (int i = 1; i <= n; i++){
		res += to_string(i);
		cmp += to_string(i);
	}
	for (int i = 1; i <= pow(10, n/2)-1; i++){
		int num = i, mul = 1;
		string temp = "";
		while (true){
			temp += to_string(num * mul);
			if (temp.size() > n)
				break;
			if (temp.size() == n){
				string tmp = temp;
				sort(tmp.begin(), tmp.end());
				if (tmp != cmp)
					break;
				if (temp > res){
					res = temp;
					break;
				}
			}
			mul++;
		}
	}
	return res;
}

int main() {
	cout << "Result: " << solve(9); 
	return 0;
}