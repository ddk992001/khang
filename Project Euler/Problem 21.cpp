// AMICABLE NUMBERS

#include <iostream>
#include <vector>

using namespace std;

int sumDivisor(int n){
	int res = 0;
	for (int i = 1; i <= n/2; i++){
		if (n % i == 0)
			res += i;
	}
	return res;
}

int solve(int n){
	int res = 0;
	vector<bool> ans;
	for (int i = 0; i < n; i++)
		ans.push_back(true);
	for (int i = 0; i < n; i++){
		if (ans[i]){
			int temp = sumDivisor(i);
			if (temp == i || !ans[temp] ||sumDivisor(temp) != i)
				ans[i] = false;
		}
	}
	for (int i = 0; i < n; i++){
		if (ans[i])
			res += i;
	}
	return res;
}

int main() {
	cout << "Result: " << solve(10000);
	return 0;
}