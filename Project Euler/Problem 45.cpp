// TRIANGULAR, PENTAGONAL, AND HEXAGONAL

#include <iostream>
#include <cmath>

using namespace std;

bool checkPentagonNumber(long long n){
	double val = (1 + sqrt(1 + 24*n)) * 1.0 / 6;
	return val == (int)val;
}

bool checkHexagonNumber(long long n){
	double val = (1 + sqrt(1 + 8*n)) * 1.0 / 4;
	return val == (int)val;
}

long long calcTriangleNumber(long long n){
	return n*(n+1)/2;
}

long long solve(long long n){
	int i = n+1;
	while (true){
		long long val = calcTriangleNumber(i);
		if (checkHexagonNumber(val) && checkPentagonNumber(val))
			return val;
		i++;
	}
}

int main() {
	cout << "Result: " << solve(285); 
	return 0;
}