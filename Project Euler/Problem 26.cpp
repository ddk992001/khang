// RECIPROCAL CYCLES

#include <iostream>
#include <map>

using namespace std;

int solve(int n){
	int res = 0, maxValue = 0;
	for (int i = 2; i <= n; i++){
		map<int, int> remainder;
		remainder[1] = 1;
		int count = 1;
		int numerator = 1, denominator = i;
		while (true){
			while (numerator < denominator)
				numerator *= 10;
			if (numerator % denominator == 0)
				break;
			numerator = numerator % denominator;
			count++;
			if (remainder.find(numerator) == remainder.end())
				remainder[numerator] = count;
			else{
				if (count - remainder[numerator] > maxValue){
					maxValue = count - remainder[numerator];
					res = i;
				}
				break;
			}
		}
	}
	return res;
}

int main() {
	cout << "Result: " << solve(1000); 
	return 0;
}