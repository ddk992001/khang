// PRIME PERMUTATIONS

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

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

string solve(int n){
	vector<int> primes;
	for (int i = pow(10, n-1); i < pow(10, n); i++){
		if (i == 1487)
			continue;
		if (i % 2 == 1 && isPrime(i))
			primes.push_back(i);
	}
	for (int i = 0; i < primes.size()-2; i++){
		string res = to_string(primes[i]);
		for (int j = i+1; j < primes.size(); j++){
			string tmp = to_string(primes[j]);
			sort(res.begin(), res.end());
			sort(tmp.begin(), tmp.end());
			if (tmp == res){
				int num = 2*primes[j] - primes[i];
				if (isPrime(num)){
					string temp = to_string(num);
					sort(temp.begin(), temp.end());
					if (temp == tmp)
						return to_string(primes[i]) + to_string(primes[j]) + to_string(num);
				}								
			}
		}
	}	
}

int main() {
	cout << "Result: " << solve(4); 
	return 0;
}