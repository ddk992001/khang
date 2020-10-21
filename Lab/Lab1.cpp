#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void inputArray(int* &a, int &n){
	cout << "Enter n: ";
	cin >> n;
	a = new int[n];
	for (int i = 0; i < n; i++){
		cout << "Enter a[" << i << "] = ";
		cin >> a[i];
	}
}

void dellocateArray(int* &a){
	delete[] a;
}

void printArray(int* a, int n){
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}
 
int findMin(int* a, int n){
	int min = a[0];
	for (int i = 1; i < n; i++){
		if (min > a[i])
			min = a[i];
	}
	return min;
}

int findMaxModulus(int* a, int n){
	int max = a[0];
	for (int i = 1; i < n; i++){
		if (max < a[i])
			max = a[i];
	}
	return max - findMin(a, n);
}

bool isAscending(int* a, int n){
	for (int i = 0; i < n-1; i++){
		if (a[i] > a[i+1])
			return false;
	}
	return true;
}

int sumOfArray(int* a, int n){
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i];
	return sum;
}

bool isPrime(int n){
	if (n < 2)
		return false;
	for (int i = 2; i <= sqrt(n); i++){
		if (n % i == 0)
			return false;
	}
	return true;
}

int countPrime(int* a, int n){
	int count = 0;
	for (int i = 0; i < n; i++){
		if (isPrime(a[i]))
			count++;
	}
	return count;
}

void reverseArray(int* &a, int* b, int n){
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = b[n-1-i];
}

int LinearSearch(int* a, int n, int key){
	for (int i = 0; i < n; i++){
		if (key == a[i])
			return i;
	}
	return -1;
}

int SentinelLinearSearch(int* a, int n, int key){
	int lastValue = a[n-1];
	a[n-1] = key;
	int i;
	for (i = 0; ; i++){
		if (key == a[i])
			break;
	}
	if (i < n-1 || lastValue == key)
		return i;
	return -1;
}

int BinarySearch(int* a, int n, int key){
	int l = 0, r = n-1;
	while (l < r){
		int mid = (l+r)/2;
		if (key > a[mid])
			l = mid+1;
		else
			r = mid;
	}
	if (a[l] == key)
		return l;
	return -1;
}

int RecursiveBinarySearch(int* a, int left, int right, int key){
	if (left == right)
		return a[left] == key ? left : -1;
	int mid = (left+right)/2;
	if (a[mid] < key)
		return RecursiveBinarySearch(a, mid+1, right, key);
	return RecursiveBinarySearch(a, left, mid, key);
}

int sumOfSquares(int n){
	if (n == 1)
		return 1;
	return n*n + sumOfSquares(n-1);
}

int GCD(int a, int b){
	if (a == 0 || b == 0)
		return a+b;
	return GCD(min(a,b), max(a,b) % min(a,b));
}

bool isPalindrome(int a[], int l, int r){
	if (l >= r)
		return true;
	if (a[l] != a[r])
		return false;
	return isPalindrome(a, l+1, r-1);
}

int Factorial(int n){
	if (n == 0 || n == 1)
		return 1;
	return n * Factorial(n-1);
}

int countDigit(int a){
	if (a / 10 == 0)
		return 1;
	return 1 + countDigit(a / 10);
}

int Fib(int n){
	if (n == 0 || n == 1)
		return n;
	return Fib(n-1) + Fib(n-2);
}

int main(){
	cout << Fib(6);
}
