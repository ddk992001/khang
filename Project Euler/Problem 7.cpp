// 10001st PRIME

#include <iostream>
#include <vector>

using namespace std;

long long solve(long long n) {
	long long count = 0;
	vector<bool> prime;
	for (int i = 2; i <= 1000000; i++)
		prime.push_back(true);
	for (int i = 2; i <= 1000000; i++){
		if (prime[i]){
			count++;
			if (count == n)
				return i; 
			for (int j = 2*i; j <= 1000000; j += i)
				prime[j] = false;
		}
	}
}

int main() {
	cout << "Result: " << solve(10001);
	return 0;
}
