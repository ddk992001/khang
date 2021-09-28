// CIRCULAR PRIMES

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int countCircular(vector<bool>& primes, int n){
	int temp = n;
	int count = 1;
	while (true){
		string str = to_string(temp);
		str.insert(str.end(), str[0]);
		str.erase(str.begin());
		if (stoi(str) == n)
			break;
		if (primes[stoi(str)]){
			count++;
			temp = stoi(str);
			primes[stoi(str)] = false;
		}
		else	
			return 0;
	}	
	return count;
}

int solve(int n){
	vector<bool> primes;
	int count = 0;
	for (int i = 0; i < n; i++)
		primes.push_back(true);
	for (int i = 2; i < n/2; i++){
		for (int j = i*2; j < n; j += i)
			primes[j] = false;
	}
	for (int i = 2; i < n; i++){
		if (primes[i]){
			count += countCircular(primes, i);
		}
	}
	return count;
}

int main() {
	cout << "Result: " << solve(1000000); 
	return 0;
}