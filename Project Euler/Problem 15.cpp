// LATTICE PATHS

#include <iostream>

using namespace std;

long long solve(long long n) {
	long long temp = 1;
	for (long long i = n+1; i <= 2*n; i++){
		temp *= i;
		temp /= (i - n);
	}
	return temp;
}

int main() {
	cout << "Result: " << solve(20);
	return 0;
}
