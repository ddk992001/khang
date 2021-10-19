// GOLDBACH'S OTHER CONJECTURE		

#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int n){
	if (n < 2)
		return false;
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0)
			return false;
	}
	return true;
}

int solve(){
	int num = 35;
	while (true){
		if (!isPrime(num)){
			int i = 1;
			bool check = false;
			while (true){
				int temp = num - 2*i*i;
				if (temp < 2)
					break;
				if (isPrime(temp)){
					check = true;
					break;
				}
				i++;
			}
			if (!check)
				return num;
		}
		num += 2;
	}
}

int main() {
	cout << "Result: " << solve(); 
	return 0;
}