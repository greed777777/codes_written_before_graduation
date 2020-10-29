//boj11650 ��ǥ�����ϱ�. //x��������, y������������ ��ǥ �����ϱ�
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
vector<pair<int, int>> input;

int N, x , y;
bool desc(pair<int,int>, pair<int, int>);

int main(void) {
	//ios_base::sync_with_stdio(false);
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		input.push_back(make_pair(x, y));
	}

	sort(input.begin(), input.end(), desc);

	for (int i = 0; i < N; i++) {
		cout << input.back().first << " " << input.back().second;
		printf("\n");
		input.pop_back();
	}
}

bool desc(pair<int,int> a, pair<int,int> b) {
	return a > b;
}