#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>

using namespace std;

int n, l, k;
int sub1, sub2;
int* output;
int score1=0, score2=0;
int total;

int main(void) {
	//cin >> n >> l >> k;
	scanf("%d%d%d", &n, &l, &k);

	output = (int*)malloc(sizeof(int)*k);

	for (int i = 0; i < n; i++)
	{
		cin >> sub1 >> sub2;
		if (sub2 <= l)
			score2++;
		else if (sub1 <= l)
			score1++;
		else
			;
	}

	if (k >= score1 + score2) {
		total = score1 * 100 + score2 * 140;
	}
	else {
		total = score2 * 140;
		total = total + (k - score2) * 100;
	}

	cout << total << endl;

	system("pause");
}