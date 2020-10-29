#include<iostream>
#define MAX 10001

using namespace std;
int N, M;
int mat[MAX] = { 0, };
int sIndex=0, eIndex=0;
int sum=0;
int mCount=0;

int main(void) {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> mat[i];
	}

	for (int i = 0; i < N; i++) {
		sIndex = i;
		eIndex = i;
		sum = mat[i];

		while ((eIndex <= N-1 )|| sum < M) {
			if (sum == M) {
				mCount++;
				break;
			}
			else if (sum < M) {
				eIndex++;
				sum = sum + mat[eIndex];
			}
			else if (sum > M) {
				break;
			}
		}
	}
	
	cout << mCount;
}