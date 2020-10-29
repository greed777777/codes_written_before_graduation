#include<iostream>

using namespace std;

char checkMult(int num1, int num2);
char checkFactor(int num1, int num2);

char output[1000] = { 0 },myCount=0;

int main(void) {

	int num1, num2;

	cin >> num1 >> num2;

	while (!(num1 == 0 && num2 == 0)) {
		if (num1 > num2)
			output[myCount] = checkMult(num1, num2);
		else
			output[myCount] = checkFactor(num1, num2);

		myCount++;
		cin >> num1 >> num2;
	}
	int i = -1;
	while (i++<myCount)
	{
		if (output[i] == 3)
			cout << "multiple" << endl;
		else if (output[i] == 1)
			cout << "neither" << endl;
		else if (output[i] == 2)
			cout << "factor" << endl;
		else
			break;
	}

	system("pause");
}

char checkMult(int num1, int num2) {
	if (num1%num2 == 0)
		return 3;
	else
		return 1;
}

char checkFactor(int num1, int num2) {
	if (num2%num1 == 0)
		return 2;
	else
		return 1;
}