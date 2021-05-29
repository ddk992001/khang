// 8 - 3 - 2002

#include <iostream>

using namespace std;

int countDivisor(long long n){
	int count = 0;
	long long temp = 0;
	for (long long i = 1; i <= n/2; i++){
		if (n % i == 0){
			if (temp == i)
				break;
			if (i == n / i){
				count++;
				break;
			}
			else{
				count += 2;
				temp = n / i;
			}
		}
	}
	return count;
}

long long solve(int n) {
	long long sum = 0;
	long long i = 1;
	while (countDivisor(sum) <= n){
		sum += i;
		i++;
	}
	return sum;
}

int main() {
	cout << "Result: " << solve(500);
	return 0;
}

