#include<iostream>

using namespace std;

int main(void) {

	int input; 

	cin >> input;
	int i = 0;
	while (i++ < input)
	{
		if (input%i == 0)
		{
			cout << "�μ�: " << i << endl;
			
		}

	}
	system("pause");
}