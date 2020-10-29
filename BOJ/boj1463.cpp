#include<iostream>

using namespace std;

int dp[1000001] = { 0,0,1,1 };
void init(int x);
int myMin(int a, int b, int c);
int myMin(int a, int b);

int main(void) {
	int input;
	cin >> input;
	init(input);
	
	
	cout << dp[input];
}

void init(int x) {
	for (int i = 4; i <= x; i++) {
		if (i % 3 == 0 && i % 2 == 0){
			dp[i] = myMin(dp[i - 1], dp[i / 3], dp[i / 2])+1;
		}
		else if (i % 3 == 0 && i % 2 != 0) {
			dp[i] = myMin(dp[i - 1], dp[i / 3]) + 1;
		}
		else if (i % 2 == 0 && i % 3 != 0) {
			dp[i] = myMin(dp[i - 1], dp[i / 2]) + 1;
		}
		else {
			dp[i] = dp[i - 1] + 1;
		}
	}
}

int myMin(int a, int b, int c) {
	if (a <= b && a <= c)
		return a;
	else if (b <= a && b <= c)
		return b;
	else
		return c;
}

int myMin(int a, int b) {
	if (a <= b)
		return a;
	else
		return b;
}