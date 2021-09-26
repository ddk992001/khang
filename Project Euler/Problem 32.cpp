// PANDIGITAL PRODUCTS

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

bool isPandigital(int n){
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0){
			string temp = to_string(i) + to_string(n / i) + to_string(n);
			sort(temp.begin(), temp.end());
			if (temp == "123456789")
				return true;			
		}
	}
	return false;
}

int solve(int n){
	int res = 0;
	for (int i = 1; i <= n; i++){
		if (isPandigital(i))
			res += i;
	}
	return res;
}

int main() {
	cout << "Result: " << solve(10000); 
	return 0;
}