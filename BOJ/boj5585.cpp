//boj 5585 �Ž����� : 1000������ ����� ��� �������� �ܵ���ȯ
#include<iostream>

using namespace std;

int main(void) {
	int input;
	int mcount=0;

	cin >> input;
	input = 1000 - input;

	while (input) {
		if (input >= 500) {
			input = input - 500;
			mcount++;
		}
		else if (input >= 100) {
			input = input - 100;
			mcount++;
		}
		else if (input >= 50) {
			input = input - 50;
			mcount++;
		}
		else if (input >= 10) {
			input = input - 10;
			mcount++;
		}
		else if (input >= 5) {
			input = input - 5;
			mcount++;
		}
		else if (input >= 1){
			input = input - 1;
			mcount++;
		}
	}

	cout << mcount;
}