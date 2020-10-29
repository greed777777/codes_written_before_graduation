#include<iostream>

using namespace std;

int is_hansu(int);

int main(void) {
	int input, mCount=0;

	cin >> input;

	for (int i = 1; i <= input; i++) {
		if (is_hansu(i) == 1)
			mCount++;
	}

	cout << mCount;

	return 0;
}

int is_hansu(int input) {

	int digit, num[4] = { 0, }, temp;
	temp = input;
	digit = 0;
	while (temp != 0) {
		temp = temp / 10;
		digit++;
	}
	
	for (int i = 0; i < digit; i++) {
		num[i] = input % 10;
		input = input / 10;
	}

	switch (digit) {
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		if (num[2] - num[1] == num[1] - num[0])
			return 1;
		else
			return 0;
	case 4:
		if (num[3] - num[2] == num[2] - num[1] && num[2] - num[1] == num[1] - num[0])
			return 1;
		else
			return 0;
	}
}