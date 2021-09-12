// SMALLEST MULTIPLE

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b){
	for (int i = max(a,b); i <= a*b; i++){
		if (i % a == 0 && i % b == 0)
			return i;
	}
}

int solve(){
	int res = 1;
	for (int i = 2; i <= 20; i++)
		res = gcd(res, i);
	return res;
}

int main(){
	cout << "Result: " << solve();
}
