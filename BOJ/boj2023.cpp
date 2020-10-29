#include<iostream>

using namespace std;
int isPrime(int a);
void interestingPrime(int a);

int nsize=1;

int main(void) {
	int N;
	cin >> N;

	for (int j = 1; j < N; j++) {
		nsize *= 10;
	}

	for (int i = 2; i < 10; i++) {
		interestingPrime(i);
	}

}

void interestingPrime(int a) {
	if (isPrime(a) == 1) {
		if (a > nsize)
			cout << a << endl;
		else {
			a = a * 10;
			int ori = a;
			for (int i = 0; i < 10; i++) {
				a = ori + i;
				interestingPrime(a);
			}
		}
	}
}

int isPrime(int a) {
	int i = 0;

	if (a == 0 || a == 1)
		return 0;
	for (i = 2; i < a; i++) {
		if (a % i == 0)
			return 0;
	}

	return 1;
}