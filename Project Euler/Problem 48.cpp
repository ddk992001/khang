// SELF POWERS		

#include <iostream>
#include <cmath>

using namespace std;

const long long SIZE = pow(10, 10);

long long solve(int n){
	long long res = 0;
	for (int i = 1; i <= n; i++){
		long long temp = i;
		for (int j = 2; j <= i; j++){
			temp *= i;
			temp %= SIZE;
		}
		res += temp;
	}
	return res % SIZE;
}

int main() {
	cout << "Result: " << solve(1000); 
	return 0;
}