// DIGIT CANCELLING FRACTIONS

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool isCancellingFraction(int num, int denom){
	string numerator = to_string(num);
	string denominator = to_string(denom);
	for (int i = 0; i < numerator.size(); i++){
		for (int j = 0; j < denominator.size(); j++){
			if (numerator[i] == denominator[j]){
				string temp1 = numerator, temp2 = denominator;
				temp1.erase(temp1.begin()+i);
				temp2.erase(temp2.begin()+j);
				if (num * 1.0 / denom == stoi(temp1) * 1.0 / stoi(temp2))
					return true;
			}
		}
	}
	return false;
}

int gcd(int a, int b){
	for (int i = min(a,b); i >= 1; i--){
		if (a % i == 0 && b % i == 0)
			return i;
	}
}

int solve(int n){
	vector<int> numerator, denominator;
	int num = 1, denom = 1;
	for (int i = pow(10,n-1)+1; i < pow(10,n)-1; i++){
		for (int j = i+1; j <= pow(10,n)-1; j++){
			if (i % 10 != 0 && j % 10 != 0 && isCancellingFraction(i, j)){
				numerator.push_back(i);
				denominator.push_back(j);
			}
		}
	}	
	for (int i = 0; i < numerator.size(); i++){
		num *= numerator[i];
		denom *= denominator[i];
	}
	return denom / gcd(num, denom);
}

int main() {
	cout << "Result: " << solve(2); 
	return 0;
}