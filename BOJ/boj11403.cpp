//boj 11403 : 플로이드-와셜 (그래프에서 노드가 연결되어있는지 확인하기)
#include<iostream>
#define MAX 100

using namespace std;

int mat[MAX][MAX] = { 0, };
int N;
void bridge(int, int);

int main(void) {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> mat[i][j];
		}
	}

	

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (mat[i][j] == 1) {//연결되었다면
				bridge(i, j);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}

	
}

void bridge(int s, int e) {//간선업데이트해주는 함수
	for (int i = 0; i < N; i++) {
		if (mat[i][s] == 1) {//s까지는 연결이 됬는데
			if(mat[i][e] == 0){//e는 연결되지 않았으면
			mat[i][e] = 1;//간선연결되어있다고 표시
			bridge(i, e);//이 간선으로 연결되는 간선 업데이트
			}
		}
	}
}