#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>

using namespace std;

void dfs(int depth, int prev);
int n, m;
int stack[8];
int pool[8];
bool deck[8];
void swap(int*, int*);
void sort(int*);


int main(void) {
	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &pool[i]);
		stack[i] = 0;
		deck[i] = 1;
	}

	sort(pool);
	dfs(0, 0);

}

void dfs(int depth, int prev) {

	if (depth == m) {
		for (int i = 0; i < m; i++) {
			printf("%d ", stack[i]);
		}
		printf("\n");
		return;
	}
	else
	{
		int start;
		if (depth == 0)
			start = 0;
		else
			start = prev;

		for (int i = start; i < n; i++) {
			stack[depth] = pool[i];
			dfs(depth + 1, i);
		}
	}
}

void sort(int* src) {

	for (int i = 0; i < n - 1; i++) {
		if (src[i] > src[i + 1]) {
			swap(src[i], src[i + 1]);
			i = -1;
		}
	}
}

void swap(int* a, int* b) {
	int* temp;

	temp = a;
	a = b;
	b = temp;
}