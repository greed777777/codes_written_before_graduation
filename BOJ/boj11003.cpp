#include<iostream>
#include<deque>
using namespace std;

using pii = pair<int, int>;

int main(void) {
	int n, m;

	deque<pii> dq;

	cin >> n >> m;
	dq.resize(m, pii(-100, 0));

	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;

		while (dq.size() && dq.front().first <= i - m)
			dq.pop_front();
		while (dq.size() && k <= dq.back().second)
			dq.pop_back();
		dq.push_back(pii(i,k));
		cout << dq.front().second << " ";
	}

	return 0;
}