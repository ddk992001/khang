// QUADRATIC PRIMES

#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int n){
	if (n < 2)
		return false;
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0)
			return false;
	}
	return true;
}

int solve(int maxA, int maxB){
	int a = 0, b = 0, maxValue = 0;
	for (int i = -maxA; i <= maxA; i++){
		for (int j = -maxB; j <= maxB; j++){
			int n = 0;
			while (isPrime(n*n + i*n + j))
				n++;
			if (maxValue < n){
				maxValue = n;
				a = i;
				b = j;
			}
		}
	}
	return a*b;
}

int main() {
	cout << "Result: " << solve(999, 1000); 
	return 0;
}