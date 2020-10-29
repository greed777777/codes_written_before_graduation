#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

void dfs(int depth);
int n, m;
int stack[8];
bool deck[8];


int main(void) {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++)
	{
		stack[i] = 0;
		deck[i] = 1;
	}
	dfs(0);
}

void dfs(int depth) {
	if (depth == m) {
		//프린트
		for (int i = 0; i < m; i++)
			cout << stack[i] << " ";
		cout << endl;
		return;
	}
	else {
		//한단계 더 깊게 탐색
		for (int i = 0; i < n; i++) {
			if (deck[i]) {
				deck[i] = 0;
				stack[depth] = i + 1;
				dfs(depth + 1);
				deck[i] = 1;
			}
		}
	}
}