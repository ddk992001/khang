// LONGEST COLLATZ SEQUENCE

#include <iostream>
#include <vector>

using namespace std;

int countTerm(long long n, vector<bool>& flag){
	int count = 1;
	long long temp = n;
	flag[n] = false;
	while (n != 1){
		if (n % 2 == 0)
			n /= 2;
		else
			n = 3*n + 1;
		count++;
		if (n < temp)
			flag[n] = false;
	}
	flag[n] = false;
	return count;
}

long long solve(long long n) {
	vector<bool> flag;
	int max = 0;
	long long res = 0;
	for (long long i = 0; i < n; i++)
		flag.push_back(true);
	for (long long i = 1; i < n; i++){
		if (flag[i]){
			int temp = countTerm(i, flag);
			if (max < temp){
				max = temp;	
				res = i;
			}
		}
	}	
	return res;
}

int main() {
	cout << "Result: " << solve(1000000);
	return 0;
}
