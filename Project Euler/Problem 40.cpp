// CHAMPERNOWNE'S CONSTANT

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(vector<int> index){
	int res = 1, num = 1, i = 0, len = 0;
	while (i < index.size()){
		string str = to_string(num);
		if (len + str.size() >= index[i]){
			res *= (int(str[index[i] - len - 1]) - 48);
			i++;
		}
		len += str.size();
		num++;
	}
	return res;
}

int main() {
	vector<int> index = {1,100,1000,10000,100000,1000000};
	cout << "Result: " << solve(index); 
	return 0;
}