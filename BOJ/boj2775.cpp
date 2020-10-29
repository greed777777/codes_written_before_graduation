#include<iostream>

using namespace std;

int output[1000] = { 0 };
int room[15][15];
void roomInit();

int main(void) {
	roomInit();

	int testCase,floor, roomN;
	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		cin >> floor >> roomN;
		output[i] = room[floor][roomN];
	}

	for (int i = 0; i < testCase; i++)
		cout << output[i] << endl;

}

void roomInit() {
	for (int i = 1; i <= 14; i++)
		room[0][i] = i;

	for (int floor = 1; floor <= 14; floor++) {
		for (int i = 1; i <= 14; i++) {
			int total = 0;
			for (int j = 1; j <= i; j++)
				total += room[floor-1][j];
			room[floor][i] = total;	//¹Ø¿¡Ãþ ÇÕ
		}
	}

	/*for (int i = 1; i <= 14; i++)
	cout << endl;*/

}