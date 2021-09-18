// LEXICOGRAPHIC PERMUTATIONS

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string solve(int n){
	int a[] = {0,1,2,3,4,5,6,7,8,9};
	int count = 1;
	do{
		if (count == n){
			string res = "";
			for (int i = 0; i < 10; i++){
				res += char(a[i]+48);
			}
			return res;
		}
		count++;
	}while (next_permutation(a, a+10));
}

int main() {
	cout << "Result: " << solve(1000000); 
	return 0;
}