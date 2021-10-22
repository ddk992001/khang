// DISTINCT PRIMES FACTORS		

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

int countPrimeFactor(int n){
	int count = 0;
	int i = 2;
	while (i <= n){
		bool check = false;
		while (true){
			if (n % i == 0 && isPrime(i)){
				n /= i;
				check = true;
			}
			else
				break;
		}
		if (check)
			count++;
		if (i == 2)
			i++;
		else
			i += 2;
	}
	return count;
}

int solve(int n){
	int firstNum = 2;
	while (true){
		bool check = true;
		int dis = 1;
		for (int i = 0; i < n; i++){
			if (countPrimeFactor(firstNum+i) != n){
				check = false;
				break;
			}
			dis++;
		}
		if (check)
			return firstNum;
		firstNum += dis;
	}
}

int main() {
	cout << "Result: " << solve(4); 
	return 0;
}