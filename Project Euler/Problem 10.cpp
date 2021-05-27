// 8 - 2 - 2002

#include <iostream>
#include <vector>

using namespace std;

long long solve(long long n) {
	long long sum = 0;
	vector<bool> flag;
	for (long long i = 0; i < n; i++)
		flag.push_back(true);
	for (long long i = 2; i < n; i++){
		if (flag[i]){
			sum += i;
			for (long long j = 2*i; j < n; j += i)
				flag[j] = false;
		}
	}
	return sum;
}

int main() {
	cout << "Result: " << solve(2000000);
	return 0;
}

