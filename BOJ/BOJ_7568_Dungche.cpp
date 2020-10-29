#include<iostream>

using namespace std;

int main(void) {
	int inputSize, input[50][2] = { 0, }, result[50] = { 0, }, output[50] = { 0, };
	int rank = 1, totalCount = 0, i = 0, j=0, count = 0;

	cin >> inputSize;
	for (i = 0; i < inputSize; i++) {
		cin >> input[i][0];
		cin >> input[i][1];
	}

	for (j = 0; j < inputSize; j++)
	{
		count=0;
		for (i = 0; i < inputSize; i++) {

			if (input[j][0] < input[i][0] && input[j][1] < input[i][1]) {
				count++;
			}
		}
		result[j] = count;
	}

	/*while(totalCount != inputSize){
		
		count = 0;
	
		for (j = 0; j < inputSize; j++) {
			if (result[j] == rank - 1)
			{
				output[j] = rank;
				count++;
			}
		}
		rank += count;
		totalCount += count;
	}*/

	for (i = 0; i < inputSize; i++) {
		cout << result[i]+1 << " ";
	}
}