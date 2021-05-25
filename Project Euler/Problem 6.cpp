// 14 - 12 - 2001

#include <iostream>
#include <cmath>

using namespace std;

long long solve(long long n) {
	return pow((1+n)*n/2,2) - n*(n+1)*(2*n+1)/6;
}

int main() {
	cout << "Result: " << solve(100);
	return 0;
}
