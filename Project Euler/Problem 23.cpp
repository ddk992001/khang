// NON-ABUNDANT SUMS

#include <iostream>
#include <vector>

using namespace std;

int sumOfDivisor(int n){
	int res = 0;
	for (int i = 1; i <= n/2; i++){
		if (n % i == 0)
			res += i;
	}
	return res;
}

vector<int> findAbundantNumbers(int n){
	vector<int> res;
	for (int i = 12; i <= n-12; i++){
		if (sumOfDivisor(i) > i)
			res.push_back(i);
	}
	return res;
}

long long solve(int n){
	long long res = 0;
	vector<int> num = findAbundantNumbers(n);
	vector<bool> ans;
	for (int i = 0; i <= n; i++)
		ans.push_back(true);
	for (int i = 0; i < num.size(); i++){
		if (num[i]*2 <= n)
			ans[num[i]*2] = false;
		else	
			break;
	}
	for (int i = 0; i < num.size()-1; i++){
		for (int j = i+1; j < num.size(); j++){
			if (num[i]+num[j] <= n)
				ans[num[i]+num[j]] = false;
		}
	}
	for (int i = 0; i < ans.size(); i++){
		if (ans[i])
			res += (long long)i;
	}
	return res;
}

int main() {
	cout << "Result: " << solve(28123);
	return 0;
}