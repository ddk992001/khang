// NUMBER SPIRAL DIAGONALS

#include <iostream>

using namespace std;

int solve(int n){
	int res = 1, dis = 2, element = 1;
	for (int i = 1; i <= n/2; i++){
		for (int j = 0; j < 4; j++){
			element += dis;
			res += element;
		}
		dis += 2;
	}
	return res;
}

int main() {
	cout << "Result: " << solve(1001); 
	return 0;
}