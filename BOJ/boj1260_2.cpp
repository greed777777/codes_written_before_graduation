#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

vector<vector<int>> link;		//간선기록
vector<int> row;				//벡터 푸시용
vector<int> isvisit;			//방문이력
vector<int> answerbfs;			//bfs탐색 결과
vector<int> answerdfs;			//dfs탐색 결과
queue<int> waiting;				//bfs탐색에 사용할 큐

int numNode, numLink, startNode;	//정점개수, 간선개수, 시작노드
int sp, ep;							//입력용 시작, 끝점

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
	//오름차순 정렬


	/*cout << endl;
	for (int i = 1; i < numNode+1; i++) {
		for (int j = 1; j < link[i].size(); j++) {
			cout << link[i][j];
		}
		cout << endl;
	}
	cout << endl;*/

	dfs(startNode);

	for (int i = 0; i < numNode + 1; i++) {//isvisit초기화
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
	if (isvisit[curr] == 0) {//아직 방문안한 노드라면
		isvisit[curr] = 1;
		answerdfs.push_back(curr);

		for (int i = 1; i < link[curr].size(); i++) {
			dfs(link[curr][i]);
		}
	}
}

void bfs(int curr) {
	if (waiting.empty() == false) {//큐가 비어있지 않으면
		waiting.pop();
	}

	if (isvisit[curr] == 0) {//아직 방문안한 노드라면
		isvisit[curr] = 1;				//방문표시
		answerbfs.push_back(curr);		//출력결과에 저장

		for (int i = 1; i < link[curr].size(); i++) {	//현재 노드에서 연결된 노드들 순회
			if (isvisit[link[curr][i]] == 0) {		//그 점이 방문한적이 없다면
				waiting.push(link[curr][i]);					//큐에 푸시
			}
		}

		if (waiting.empty() == false) {			//큐가 비어있지 않으면
			bfs(waiting.front());				//큐순서대로 하나씩 꺼내서 반복
		}

	}
}
