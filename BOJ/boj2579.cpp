#include<iostream>
#define MAX 302
#define SW2 1
#define SW1 0
using namespace std;
int steps[MAX];
int mymax(int, int);
typedef struct dp {
	int point;
}dp;

dp mydp[MAX] = {};

int main(void) {
	int s, points, s1;

	cin >> s;
	s1 = s + 1;
	for (int i = 1; i < s1; i++) {
		cin >> points;
		steps[i] = points;
	}

	//초반 부분해 설정
	mydp[1].point = steps[1];
	mydp[2].point = steps[1] + steps[2];
	mydp[3].point = mymax(steps[1] + steps[3], steps[2] + steps[3]);

	for (int i = 4; i < s1; i++) {
		mydp[i].point = mymax(mydp[i - 3].point + steps[i - 1] + steps[i], mydp[i - 2].point + steps[i]);
	}

	cout <<mydp[s].point;
}

int mymax(int a, int b) {//앞에것이 큰경우에만 앞에것 리턴
	if (a > b)
		return a;
	else
		return b;
}