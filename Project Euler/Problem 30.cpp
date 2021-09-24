// DIGIT FIFTH POWERS

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool checkNum(int n, int power){
	int sum = 0, temp = n;
	while (temp != 0){
		sum += pow((temp % 10), power);
		temp /= 10;
	}
	return sum == n;
}

int solve(int n){
	vector<int> res;
	int sum = 0;
	for (int i = 2; i < pow(10, n+1)-1; i++){
		if (checkNum(i, n))
			res.push_back(i);
	}
	for (int i = 0; i < res.size(); i++)
		sum += res[i];
	return sum;
}

int main() {
	cout << "Result: " << solve(5); 
	return 0;
}