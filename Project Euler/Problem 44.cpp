// PENTAGON NUMBERS

#include <iostream>
#include <cmath>

using namespace std;

bool checkPentagonNumber(int n){
	float val = (1 + sqrt(1 + 24*n)) * 1.0 / 6;
	return val == (int)val;
}

int solve(){
	int i = 2;
	while (true){
		int tmp1 = ((3*i-1)*i)/2;
		for (int j = 1; j < i; j++){
			int tmp2 = ((3*j-1)*j)/2;
			if (checkPentagonNumber(tmp1+tmp2) && checkPentagonNumber(tmp1-tmp2))
				return tmp1 - tmp2;
		}
		i++;
	}
}

int main() {
	cout << "Result: " << solve(); 
	return 0;
}