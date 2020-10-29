//boj 11403 : �÷��̵�-�ͼ� (�׷������� ��尡 ����Ǿ��ִ��� Ȯ���ϱ�)
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
			if (mat[i][j] == 1) {//����Ǿ��ٸ�
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

void bridge(int s, int e) {//����������Ʈ���ִ� �Լ�
	for (int i = 0; i < N; i++) {
		if (mat[i][s] == 1) {//s������ ������ ��µ�
			if(mat[i][e] == 0){//e�� ������� �ʾ�����
			mat[i][e] = 1;//��������Ǿ��ִٰ� ǥ��
			bridge(i, e);//�� �������� ����Ǵ� ���� ������Ʈ
			}
		}
	}
}