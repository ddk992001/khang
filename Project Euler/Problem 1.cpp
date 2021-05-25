/*#include <iostream>

using namespace std;

long long sumOfThree(long long n) {
	long long index = ((n - 1) / 3);
	return index * (2 * 3 + (index - 1) * 3) / 2;
}

long long sumOfFive(long long n) {
	long long index = ((n - 1) / 5);
	return index * (2 * 5 + (index - 1) * 5) / 2;
}

long long sumOfThreeAndFive(long long n) {
	long long index = ((n - 1) / 15);
	return index * (2 * 15 + (index - 1) * 15) / 2;
}

long long solve(long long n) {
	return sumOfThree(n) + sumOfFive(n) - sumOfThreeAndFive(n);
}

int main() {
	long long n;
	cout << "Enter n: ";
	cin >> n;
	cout << "Result: " << solve(n);
	return 0;
}*/