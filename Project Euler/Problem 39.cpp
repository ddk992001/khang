// INTEGER RIGHT TRIANGLES

#include <iostream>

using namespace std;

int countRightTriangles(int p){
	int count = 0;
	for (int i = 3; i <= p-2; i++){
		for (int j = 1; j <= p-i-1; j++){
			int k = p-i-j;
			if (i*i + j*j == k*k || i*i + k*k == j*j || j*j + k*k == i*i)
				count++;
		}
	}
	return count;
}

int solve(int n){
	int res = -1, max = 0;
	for (int i = 12; i <= n; i++){
		int rightTriangle = countRightTriangles(i);
		if (rightTriangle > max){
			max = rightTriangle;
			res = i;
		}
	}
	return res;
}

int main() {
	cout << "Result: " << solve(1000); 
	return 0;
}