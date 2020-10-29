#include<iostream>

using namespace std;

int answer(int,int, int);
int solution=0;

int main(void) {
	int inputN=0, inputR=0, inputC=0;

	cin >> inputN;
	cin >> inputR;
	cin >> inputC;

	cout << answer(inputN, inputR, inputC);
}

int answer(int n, int r, int c) {
	
	if (n == 1)
	{
		if (r == 0 && c == 0)
			solution += 0;
		else if (r == 0 && c == 1)
			solution += 1;
		else if (r == 1 && c == 0)
			solution += 2;
		else
			solution += 3;

		return solution;
	}

	int boundary = 1;
	for (int i = 1; i < n; i++)//경계선 설정
		boundary *= 2;

	int square = boundary * boundary;

	switch (r < boundary) {
	case true://표면 4등분했을때 위쪽
		if (c < boundary)//표면 4등분 했을때 왼쪽
		{
			solution += square * 0;
			return answer(n - 1, r, c);
		}
		else {//오른쪽
			solution += square * 1;
			return answer(n - 1, r, c-boundary);
		}
	case false://표면 4등분했을때 아래쪽
		if (c < boundary)//표면 4등분 했을때 왼쪽
		{
			solution += square * 2;
			return answer(n - 1, r-boundary, c);
		}
		else {//오른쪽
			solution += square * 3;
			return answer(n - 1, r-boundary, c-boundary);
		}
	}

}