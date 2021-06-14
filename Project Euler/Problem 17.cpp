// 18 - 5 - 2002

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(int n){
	vector<string> a = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	vector<string> b = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
	vector<string> c = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
	int count = 0;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			for (int k = 0; k < 10; k++){
				if (i == 0 && j == 0 && k != 0)
					count += a[k-1].size();
				else if (i == 0){
					if (j == 1)
						count += b[k].size();
					else{
						count += c[j-2].size();
						if (k != 0)
							count += a[k-1].size(); 
					}
				}
				else{
					if (j == 0 && k == 0)
						count += a[i-1].size() + 7;
					else if (j == 0)
						count += a[i-1].size() + 10 + a[k-1].size();
					else if (k == 0 && j == 1)
						count += a[i-1].size() + 13;
					else if (k == 0 && j != 1)
						count += a[i-1].size() + 10 + c[j-2].size();
					else{
						if (j == 1)
							count += a[i-1].size() + 10 + b[k].size();
						else
							count += a[i-1].size() + 10 + c[j-2].size() + a[k-1].size(); 
					}
				}
			}
		}
	}
	return count + 11;
}

int main() {
	cout << "Result: " << solve(1000);
	return 0;
}
