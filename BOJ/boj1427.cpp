//boj1427 : ��Ʈ�λ��̵� //�� �Է¹ް� �� �ȿ��� �������������ϱ�
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

vector<int> v;
bool desc(int a, int b) {
	return a > b;
}

int main(void) {
	string input;
	cin >> input;

	for (int i = 0; i < input.size(); i++) {
		v.push_back(input.at(i)-'0');
	}
	sort(v.begin(), v.end(), desc);


	for (int i = 0; i < v.size(); i++) {
		cout << v[i];
	}
}