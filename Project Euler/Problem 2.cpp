// 19 - 10 - 2001 

#include <iostream>

using namespace std;

long long solve(long long n) {
	long long sum = 2;
	long long a = 1, b = 2;
	while (true) {
		long long temp = a + b;
		a = b;
		b = temp;
		if (temp % 2 == 0)
			sum += temp;
		if (temp > n)
			break;
	}
	return sum;
}

int main() {
	cout << "Result: " << solve(4000000);
	return 0;
}
