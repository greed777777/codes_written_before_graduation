//boj 2178 �̷�Ž�� : 1,1 ~ n,m���� �̵��Ҷ� �������ϴ� �ּ�ĭ�� �� ��ȯ
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

int answer=500;

void bfs(int x, int y, int cost);
int n, m;			//n���� ������, m���� ������. n���� y, m���� x
//vector<vector<int>> mat;
//vector<int> tmp;
//int* mat;
int mat[101][101] = { 0, };
string t;

int main(void) {
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);
	//cout.tie(NULL);
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		//cin >> t;
		for (int j = 0; j < m; j++) {
			scanf("%1d", &mat[i][j]);
			//mat[i][j] = (t.at(j) - '0');
		}
	}

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
		{
			cout << mat[i*n+j];
		}
		cout << endl;
	}*/

	bfs(0, 0, 1);
	cout << answer;


}

void bfs(int x, int y, int cost) {
	if (cost > answer)
		return;

	if (x == n-1 && y == m-1 && cost < answer)//���ο� �ذ� �� ���� ���̸� ��ü
	{
		answer = cost;
		return;
	}

	/*if (y + 1 <= m-1) {
		if (mat[x*n + y + 1]&& (((n-1)-x) + ((m-1)-y) + cost) < answer)
			bfs(x, y + 1, cost + 1);
	}
	if (x + 1 <= n-1) {
		if (mat[(x + 1)*n+y] && (((n - 1) - x) + ((m - 1) - y) + cost) < answer)
			bfs(x + 1, y, cost + 1);
	}
	if (x - 1 >= 0) {
		if (mat[(x - 1)*n+y] && (((n - 1) - x) + ((m - 1) - y) + cost) < answer)
			bfs(x - 1, y, cost + 1);
	}
	if (y - 1 >= 0) {
		if (mat[x*n+(y - 1)] && (((n - 1) - x) + ((m - 1) - y) + cost) < answer)
			bfs(x, y - 1, cost + 1);
	}*/
	int comp = (((n - 1) - x) + ((m - 1) - y) + cost);
	if (y + 1 <= m - 1) {
		if (mat[x][y + 1] && comp < answer)
			bfs(x, y + 1, cost + 1);
	}
	if (x + 1 <= n - 1) {
		if (mat[x + 1][y] && comp < answer)
			bfs(x + 1, y, cost + 1);
	}
	if (x - 1 >= 0) {
		if (mat[x - 1][y] && comp < answer)
			bfs(x - 1, y, cost + 1);
	}
	if (y - 1 >= 0) {
		if (mat[x][y - 1] && comp < answer)
			bfs(x, y - 1, cost + 1);
	}
}