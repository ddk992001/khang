// LARGEST PRIME FACTOR

#include <iostream>

using namespace std;

int solve(long long n){
	long long max = 0;
	long long i = 2;
	while (i <= n){
		while (n % i == 0){
			n /= i;
			max = i;
		}
		i++;
	}
	return max;
}

int main(){
	cout << "Result: " << solve(600851475143);
}
