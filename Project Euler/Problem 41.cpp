// PANDIGITAL PRIME

#include <iostream>
#include <algorithm>
#include <string>
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

string solve(){
	for (int i = 9; i >= 1; i--){
		int* a = new int[i];
		int sum = 0;
		for (int j = i; j >= 1; j--){
			a[i-j] = j;
			sum += j;
		}
		if (sum % 3 != 0){
			do{
				string tmp = "";
				for (int j = 0; j < i; j++)
					tmp += to_string(a[j]);
				int n = stoi(tmp);
				if (isPrime(n)){
					delete[] a;
					return tmp;
				}
			} while (prev_permutation(a, a+i));
		}
		delete[] a;
	}	
}

int main() {
	cout << "Result: " << solve(); 
	return 0;
}