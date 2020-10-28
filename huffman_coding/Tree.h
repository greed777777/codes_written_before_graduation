#pragma once
#include<iostream>
#include<string>
#define NOT_YET 0
#define MOVED 1
#define LEFT 0
#define RIGHT 1

using namespace std;

typedef struct Node {
	string s;
	int apearNum;
	Node* next;
	Node* left;
	Node* right;
}Node;

class huffmanTree {
private:
	Node* _root;
	Node* _head;

public:
	huffmanTree() { _root = NULL; _head = NULL; }

	void PrintTree();								//트리 출력함수
	void FPrintTree(ofstream &fout);
	Node* InsertList(char c);
	Node* InsertList(string s);						//노드를 리스트로서 취급. 헤드에서부터 s탐색 일치하면 출현횟수 ++
	Node* InsertList(Node* newNode);				//생성된 부모노드의 출현횟수를 비교하기위해 다시 리스트로 넣어주는 함수
	Node* MergeChildren(Node* left, Node* right);	//왼쪽노드 오른쪽노드를 매개변수로 넣어주면 그 두개를 자식으로 갖는 부모노드생성 후 반환
	Node* ExcludeMinNode(Node* _head);				//노드를 리스트로 취급. 헤드를 넣으면 출현횟수 가장작은 노드 반환 & 리스트에서 제외
	Node* PlantTreeFrom();
	Node* PlantTreeFrom(ifstream &fin);
	Node* ReturnRoot();

	string Encoding(char c);

	int GetListLength();
	void Inorder(Node* curr);
	
};

Node* huffmanTree::InsertList(char c) {
	if (_head == NULL)
	{
		Node* newNode = new Node;
		newNode->apearNum = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->s = c;
		newNode->next = NULL;

		_head = newNode;

		return newNode;
	}
	else
	{
		Node* curr = _head;
		string s;
		s = c;

		while (curr != NULL)
		{
			if (curr->s == s)
			{
				curr->apearNum++;

				return curr;
			}
			curr = curr->next;
		}

		curr = _head;

		while (curr->next != NULL)
			curr = curr->next;

		Node* newNode = new Node;
		newNode->apearNum = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->s = s;
		newNode->next = NULL;

		curr->next = newNode;

		return newNode;
	}
}

Node* huffmanTree::InsertList(string s) {
	if (_head == NULL)
	{
		Node* newNode = new Node;
		newNode->apearNum = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->s = s;
		newNode->next = NULL;

		_head = newNode;
		
		return newNode;
	}
	else
	{
		Node* curr = _head;
		
		while (curr != NULL)
		{
			if (curr->s == s)
			{
				curr->apearNum++;

				return curr;
			}
			curr = curr->next;
		}
		
		curr = _head;
		
		while (curr->next != NULL)
			curr = curr->next;
		
		Node* newNode = new Node;
		newNode->apearNum = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->s = s;
		newNode->next = NULL;

		curr->next = newNode;

		return newNode;
	}

}

Node* huffmanTree::InsertList(Node* newNode) {
	Node *curr,*parent;
	curr = parent = _head;
	
	if (_head == NULL)
	{
		_head = newNode;
		return newNode;
	}
	else
	{

		while (curr != NULL)
		{
			parent = curr;
			curr = curr->next;	//마지막노드로 이동
		}
		parent->next = newNode;

		return newNode;
	}
}

Node* huffmanTree::MergeChildren(Node* left, Node* right) {
	Node* newParent = new Node;
	newParent->left = left;
	newParent->right = right;
	newParent->next = NULL;
	newParent->apearNum = left->apearNum + right->apearNum;
	newParent->s = left->s + right->s;

	return newParent;
}

Node* huffmanTree::ExcludeMinNode(Node* _head) {
	Node* curr, *parent, *minNode;
	minNode = curr = parent = _head;

	if (_head->next == NULL)						//리스트가 단일 노드일경우
	{
		minNode = _head;							//그노드를 최소노드로 선정
		huffmanTree::_head = NULL;					//헤드를 비움
		return minNode;
	}

	while (curr != NULL)							//최소노드를 찾음
	{
		if (curr->apearNum < minNode->apearNum)
			minNode = curr;							//최소노드 선정
		curr = curr->next;
	}
	curr = _head;									//최소노드의 위치를 찾기위해 헤드로 이동
	while (1)
	{
		if (curr == minNode)						//첫노드가 최소노드라면
		{
			huffmanTree::_head = huffmanTree::_head->next;		//헤드를 다음노드로
			break;
		}
		if (curr->next == minNode)					//지금노드의 다음노드가 최소노드라면
			break;									//지금노드를 가르킨 채로 반복문 탈출
		curr = curr->next;							//그렇지 않으면 다음노드로 이동
	}

	if(curr->next == minNode)						//최소노드를 탐색해서 알아냈다면
		curr->next = curr->next->next;				//최소노드를 리스트에서 제거
													//아니라면 위에서 제거했으므로 넘어감

	return minNode;									//최소노드 반환
}

Node* huffmanTree::PlantTreeFrom(void) {
	int iterator = GetListLength();

	for (int i = 0; i < iterator - 1; i++) {
		Node* left = ExcludeMinNode(_head);
		Node* right = ExcludeMinNode(_head);
		Node* parent = MergeChildren(left, right);
		
		InsertList(parent);
	}

	_root = _head;

	return _root;
}

int huffmanTree::GetListLength(void) {
	Node* curr;
	curr = _head;
	int count = 0;

	while (curr != NULL)
	{
		curr = curr->next;
		count++;
	}

	return count;
}

void huffmanTree::PrintTree() {
	Inorder(_root);
}

void huffmanTree::Inorder(Node* curr) {
	if (curr->left != NULL)
		Inorder(curr->left);
	cout <<"\""<< curr->s <<"\""<< "(" << curr->apearNum << ")" << endl;
	if (curr->right != NULL)
		Inorder(curr->right);
}

string huffmanTree::Encoding(char c) {
	Node* curr = _root;
	string codedText = "";
	bool checkMove = NOT_YET;
	bool direction;

	while (curr->left != NULL && curr->right != NULL) {			//자식노드가 모두 NULL이라면 즉, 말단노드가 될때까지 이동
		for (int i = 0; i < curr->left->s.length(); i++) {
			if (curr->left->s.at(i) == c)						//왼쪽노드에 찾는 문자열이 있으면
			{
				codedText = codedText + "0";					//왼쪽으로 이동하므로 코드에 0추가
				direction = LEFT;								//이동방향에 왼쪽 대입
				checkMove = MOVED;
			}
			
			if (i == curr->left->s.length()-1 && checkMove == NOT_YET)	//왼쪽노드의 모든문자와 비교가 끝났고, 이동이 없었을시
			{
				codedText = codedText + "1";					//오른쪽으로 이동하므로 코드에 1추가
				direction = RIGHT;								//이동방향에 오른쪽 대입
				checkMove = MOVED;
			}
		}
		if (direction == LEFT)									//방향 왼쪽이면
		{
			curr = curr->left;									//왼쪽으로 이동
			checkMove = NOT_YET;								//다음비교를 위해 초기화
		}
		else													//방향 왼쪽 아니면 즉, 오른쪽이면
		{
			curr = curr->right;									//오른쪽으로 이동
			checkMove = NOT_YET;								//다음비교를 위해 초기화
		}

	}

	return codedText;
}

Node* huffmanTree::ReturnRoot() {
	return _root;
}

void huffmanTree::FPrintTree(ofstream &fout) {
	Node* curr = _head;

	while (curr != NULL)
	{
		fout << curr->s << '\t' << curr->apearNum << '\t';
		curr = curr->next;
	}
}

Node* huffmanTree::PlantTreeFrom(ifstream &fin) {
	char character;
	string iter;
	int i;
	while (!fin.eof())
	{
		fin.get(character);
		fin >> iter;
		if(character != '\t')
			for (i = 0; i < stoi(iter); i++)
				InsertList(character);
	}

	PlantTreeFrom();

	return _root;
}

