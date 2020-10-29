//boj 11399 ATM : atm기 최소사용시간 구하기.
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void) {
	vector<int> time;

	int numPeople, input, sum=0,output=0;

	cin >> numPeople;

	for (int i = 0; i < numPeople; i++) {
		cin >> input;
		time.push_back(input);
	}

	sort(time.begin(), time.end());

	for (int i = 0; i < time.size(); i++) {
		output = output + sum + time[i];
		sum = sum + time[i];
	}

	cout << output;
}