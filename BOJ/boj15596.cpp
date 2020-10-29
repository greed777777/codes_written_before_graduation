#include<iostream>

using namespace std;

int main(void) {
	//int input;
	char* cmd;

	//cin >> input;
	cmd = (char*)malloc(sizeof(char) * 10);

	/*for (int i = 0; i < input; i++) {
		cin >> cmd;

		cout << cmd;
	}*/

	for (int i = 0; i < 5; i++) {
		cin >> cmd;
		if (cmd == "push\0") {
			cout << "match" << endl;
		}
	}
}