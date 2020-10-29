//boj5874 �Ҹ� ã�ƶ�. : ���ڿ��Է¹޾Ƽ� ��ġ�ϴ� ���ڿ� ����Ǽ� ã��
#include<iostream>
#define MAX 25000
using namespace std;

string input;
int output = 0;

int front[MAX] = { 0, };
int rear[MAX] = { 0, };
int fsize = 0;
int rsize = 0;
int fcount = 0;

int N;

int main(void) {
	cin >> input;


	for (unsigned int i = 1; i < input.size(); i++) {
		if (input.at(i - 1) == input.at(i)) {
			if (input.at(i) == '(') {
				front[fsize++] = i;
			}
			else {
				rear[rsize++] = i;
			}
		}
	}
	int rinit = 0;
	while (fcount < fsize) {
		//cout << front.front() << endl;
		//front.pop_front();
		if (fsize == 0 || rsize == 0)
			break;

		while (front[fcount] > rear[rinit]) {
			rinit++;
		}

		if (rinit > rsize)
			break;

		for (unsigned int i = rinit; i < rsize; i++) {
			if (front[fcount] < rear[i])
				output++;
		}

		fcount++;
	}

	cout << output;
}