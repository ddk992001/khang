// SUB-STRING DIVISIBILITY

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

long long solve(int num[]){
	int a[] = {0,1,2,3,4,5,6,7,8,9};
	long long res = 0;
	do{
		string temp = "";
		for (int i = 0; i < 10; i++)
			temp += to_string(a[i]);
		if (temp[0] == '0')
			continue;
		int j = 0;
		bool check = true;
		for (int i = 1; i < 8; i++){
			int sum = int(temp[i])*100 + int(temp[i+1])*10 + int(temp[i+2]) - 5328;
			if (sum % num[j] != 0){
				check = false;
				break;
			}
			j++;
		}
		if (check)
			res += stoll(temp);
	} while (next_permutation(a, a+10));
	return res;
}

int main() {
	int num[] = {2,3,5,7,11,13,17};
	cout << "Result: " << solve(num); 
	return 0;
}