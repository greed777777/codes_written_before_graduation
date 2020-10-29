#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>

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
	int start;
	if (depth == 0)
		start = 0;
	else
		start = stack[depth - 1];
	if (depth == m) {
		for (int i = 0; i < m; i++) {
			printf("%d ", stack[i]+1);
		}
		printf("\n");
		return;
	}
	else
		for (int i = start; i < n; i++) {
			stack[depth] = i;
			dfs(depth + 1);
		}
}