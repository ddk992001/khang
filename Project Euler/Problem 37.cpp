// TRUNCATABLE PRIMES

#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int SIZE = 1000000;

bool isTruncatable(vector<bool> primes, int n){
	string num = to_string(n);
	while (num != ""){
		int temp = stoi(num);
		if (!primes[temp])
			return false;
		num.erase(num.begin());
	}
	num = to_string(n);
	while (num != ""){
		int temp = stoi(num);
		if (!primes[temp])
			return false;
		num.erase(num.end()-1);
	}
	return true;
}

int solve(){
	vector<bool> primes;
	int sum = 0;
	for (int i = 0; i < SIZE; i++)
		primes.push_back(true);
	primes[0] = false;
	primes[1] = false;
	for (int i = 2; i < SIZE/2; i++){
		for (int j = i*2; j < SIZE; j += i){
			primes[j] = false;
		}
	}	
	for (int i = 11; i < SIZE; i++){
		if (isTruncatable(primes, i))
			sum += i;
	}
	return sum;
}

int main() {
	cout << "Result: " << solve(); 
	return 0;
}