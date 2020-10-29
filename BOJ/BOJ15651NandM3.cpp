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
	if (depth == m) {
		for (int i = 0; i < m; i++) {
			printf("%d ", stack[i]);
		}
		printf("\n");
		return;
	}
	else
		for (int i = ; i < n; i++) {

			deck[i] = 0;
			stack[depth] = i + 1;
			dfs(depth + 1);
			deck[i] = 1;

		}
}