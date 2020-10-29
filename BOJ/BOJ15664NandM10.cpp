#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>

using namespace std;

void dfs(int depth, int prev);
int* search(int);
int n, m, actual;
int stack[8];
int pool[8];
int temp;
int deck[8] = { 0 };
void swap(int*, int*);
void sort(int*);


int main(void) {
	scanf("%d%d", &n, &m);
	actual = n;
	for (int i = 0; i < actual; i++)
	{
		scanf("%d", &temp);

		if (search(temp) == NULL)
		{
			pool[i] = temp;
			stack[i] = 0;
			deck[i] = 1;
		}
		else
		{
			(*search(temp))++;
			i--;
			actual--;
		}

	}

	sort(pool);
	dfs(0, 0);

	system("pause");

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

		for (int i = prev; i < actual; i++) {
			if (deck[i] > 0)
			{
				deck[i]--;
				stack[depth] = pool[i];
				dfs(depth + 1, i);
				deck[i]++;
			}
		}
	}
}

void sort(int* src) {

	for (int i = 0; i < actual - 1; i++) {
		if (src[i] > src[i + 1]) {
			swap(src[i], src[i + 1]);
			swap(deck[i], deck[i + 1]);
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

int* search(int a) {
	for (int i = 0; i < actual; i++) {
		if (a == pool[i])
			return &deck[i];
	}
	return NULL;
} 