// SPECIAL PYTHAGOREAN TRIPLET

#include <iostream>

using namespace std;

int solve() {
	for (int i = 1; i < 500; i++){
		for (int j = 1; j < 500; j++){
			for (int k = 1; k < 500; k++){
				if (i + j + k == 1000 && i*i + j*j == k*k)
					return i*j*k;
			}
		}
	}
}

int main() {
	cout << "Result: " << solve();
	return 0;
}

