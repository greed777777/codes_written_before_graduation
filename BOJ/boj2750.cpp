//boj2750 정렬 // 입력 1000개이하일때 오름차순정렬하기
#include<iostream>
#define MAX 1001
using namespace std;

int input[MAX];

int main(void) {
	int N=0;

	cin >> N;

	for (int i = 0; i < N; i++) {
		input[i] = 1001;
	}
	
	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}
	int min= input[0];
	int minIndex=0;
	int tmp;

	for (int i = 0; i < N; i++) {
		minIndex = i;
		min = input[i];
		for (int j = i; j < N; j++) {
			if (min > input[j])
			{
				min = input[j];
				minIndex = j;
			}
		}
		tmp = input[minIndex];
		input[minIndex] = input[i];
		input[i] = tmp;
	}

	for (int i = 0; i < N; i++) {
		cout << input[i] << endl;
	}
}