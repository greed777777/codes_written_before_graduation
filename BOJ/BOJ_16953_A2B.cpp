#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <queue>

using namespace std;
long int A, B;
queue<pair<long int, long int>> res;
long int cnt;
long int bfs() {
	res.push(make_pair(A, cnt));
	while (!res.empty()) {
		long int now = res.front().first;
		long int ncnt = res.front().second;
		res.pop();
		if (now < B) {
			if (now * 2 <= B)
				res.push(make_pair(now * 2, ncnt + 1));
			if (now * 10 + 1 <= B)
				res.push(make_pair(now * 10 + 1, ncnt + 1));

			//printf("%d %d %d\n", now, now * 2, now * 10 + 1);
		}
		else if (now == B) {
			return ncnt + 1;
		}
	}
	return -1;
}

int main() {
	scanf("%d %d", &A, &B);
	printf("%d", bfs());
	//   if (flag == 1) printf("-1\n");
	return 0;
}