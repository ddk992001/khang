// LARGEST PALINDROME PRODUCT

#include <iostream>
#include <vector>

using namespace std;

bool isPalindrome(int n){
	vector<int> a;
	while (n != 0){
		a.push_back(n % 10);
		n /= 10;
	}
	for (int i = 0; i < a.size(); i++){
		if (a[i] != a[a.size()-1-i])
			return false;
	}
	return true;
}

int solve(){
	int max = 0;
	for (int i = 999; i >= 100; i--){
		for (int j = 999; j >= 100; j--){
			int temp = i*j;
			if (isPalindrome(temp) && temp > max)
				max = temp;
		}
	}
	return max;
}

int main(){
	cout << "Result: " << solve();
}
