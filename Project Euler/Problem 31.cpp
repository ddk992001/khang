// COIN SUMS

#include <iostream>
#include <vector>

using namespace std;

int solve(vector<int> coins){
	vector<int> possibleVal;
	int count = 0;
	for (int i = 0; i < coins.size()-1; i++)
		possibleVal.push_back(coins[coins.size()-1] / coins[i]);
	for (int a = 0; a < possibleVal[0]; a++){
		for (int b = 0; b < possibleVal[1]; b++){
			for (int c = 0; c < possibleVal[2]; c++){
				for (int d = 0; d < possibleVal[3]; d++){
					for (int e = 0; e < possibleVal[4]; e++){
						for (int f = 0; f < possibleVal[5]; f++){
							for (int g = 0; g < possibleVal[6]; g++){
								if (a*coins[0] + b*coins[1] + c*coins[2] + d*coins[3] + e*coins[4] + f*coins[5] + g*coins[6] == coins[7])
									count++;
							}
						}
					}
				}
			}
		}
	}
	return count + 1 + possibleVal.size();
}

int main() {
	vector<int> coins = {1,2,5,10,20,50,100,200};
	cout << "Result: " << solve(coins); 
	return 0;
}