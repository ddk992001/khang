// DIGIT FACTORIALS

#include <iostream>
#include <vector>

using namespace std;

int factorial(int n){
	int res = 1;
	for (int i = 2; i <= n; i++)
		res *= i;
	return res;
}

int solve(){
	vector<int> num;
	int res = 0;
	for (int i = 10; i <= 1000000; i++){
		int temp = i;
		int sum = 0;
		while (temp != 0){
			sum += factorial(temp % 10);
			if (sum > i)
				break;
			temp /= 10;
		}
		if (sum == i)
			num.push_back(i);
	}
	for (int i = 0; i < num.size(); i++)
		res += num[i];
	return res;
}

int main() {
	cout << "Result: " << solve(); 
	return 0;
}