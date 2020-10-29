#include<iostream>

using namespace std;

int testCase=0,h=0,w=0,n=0;
int output[1000] = { 0, };


int main(void) {
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		int answer;
		cin >> h >> w >> n;
		answer = (n % (h +1)) * 100;
		answer = answer + (n / h) + 1;
		output[i] = answer;
	}

	for (int i = 0; i < testCase; i++) {
		cout << output[i] << endl;
	}
}