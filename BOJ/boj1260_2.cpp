#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

vector<vector<int>> link;		//�������
vector<int> row;				//���� Ǫ�ÿ�
vector<int> isvisit;			//�湮�̷�
vector<int> answerbfs;			//bfsŽ�� ���
vector<int> answerdfs;			//dfsŽ�� ���
queue<int> waiting;				//bfsŽ���� ����� ť

int numNode, numLink, startNode;	//��������, ��������, ���۳��
int sp, ep;							//�Է¿� ����, ����

void dfs(int);
void bfsold(int);
void bfs(int);

int main(void) {

	cin >> numNode >> numLink >> startNode;
	//cin >> numLink;
	//cin >> startNode;

	row.push_back(0);

	for (int i = 0; i < numNode + 1; i++) {
		link.push_back(row);
		isvisit.push_back(0);
	}

	for (int i = 0; i < numLink; i++) {
		cin >> sp;
		cin >> ep;

		link[sp].push_back(ep);
		link[ep].push_back(sp);
	}

	for (int i = 0; i < numNode + 1; i++) {
		sort(link[i].begin(), link[i].end());
	}
	//�������� ����


	/*cout << endl;
	for (int i = 1; i < numNode+1; i++) {
		for (int j = 1; j < link[i].size(); j++) {
			cout << link[i][j];
		}
		cout << endl;
	}
	cout << endl;*/

	dfs(startNode);

	for (int i = 0; i < numNode + 1; i++) {//isvisit�ʱ�ȭ
		isvisit[i] = 0;
	}

	bfs(startNode);

	for (int i = 0; i < answerdfs.size(); i++) {
		cout << answerdfs[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < answerbfs.size(); i++) {
		cout << answerbfs[i] << " ";
	}

	return 0;
}

void dfs(int curr) {
	if (isvisit[curr] == 0) {//���� �湮���� �����
		isvisit[curr] = 1;
		answerdfs.push_back(curr);

		for (int i = 1; i < link[curr].size(); i++) {
			dfs(link[curr][i]);
		}
	}
}

void bfs(int curr) {
	if (waiting.empty() == false) {//ť�� ������� ������
		waiting.pop();
	}

	if (isvisit[curr] == 0) {//���� �湮���� �����
		isvisit[curr] = 1;				//�湮ǥ��
		answerbfs.push_back(curr);		//��°���� ����

		for (int i = 1; i < link[curr].size(); i++) {	//���� ��忡�� ����� ���� ��ȸ
			if (isvisit[link[curr][i]] == 0) {		//�� ���� �湮������ ���ٸ�
				waiting.push(link[curr][i]);					//ť�� Ǫ��
			}
		}

		if (waiting.empty() == false) {			//ť�� ������� ������
			bfs(waiting.front());				//ť������� �ϳ��� ������ �ݺ�
		}

	}
}
