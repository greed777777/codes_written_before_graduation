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

	void PrintTree();								//Ʈ�� ����Լ�
	void FPrintTree(ofstream &fout);
	Node* InsertList(char c);
	Node* InsertList(string s);						//��带 ����Ʈ�μ� ���. ��忡������ sŽ�� ��ġ�ϸ� ����Ƚ�� ++
	Node* InsertList(Node* newNode);				//������ �θ����� ����Ƚ���� ���ϱ����� �ٽ� ����Ʈ�� �־��ִ� �Լ�
	Node* MergeChildren(Node* left, Node* right);	//���ʳ�� �����ʳ�带 �Ű������� �־��ָ� �� �ΰ��� �ڽ����� ���� �θ������ �� ��ȯ
	Node* ExcludeMinNode(Node* _head);				//��带 ����Ʈ�� ���. ��带 ������ ����Ƚ�� �������� ��� ��ȯ & ����Ʈ���� ����
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
			curr = curr->next;	//���������� �̵�
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

	if (_head->next == NULL)						//����Ʈ�� ���� ����ϰ��
	{
		minNode = _head;							//�׳�带 �ּҳ��� ����
		huffmanTree::_head = NULL;					//��带 ���
		return minNode;
	}

	while (curr != NULL)							//�ּҳ�带 ã��
	{
		if (curr->apearNum < minNode->apearNum)
			minNode = curr;							//�ּҳ�� ����
		curr = curr->next;
	}
	curr = _head;									//�ּҳ���� ��ġ�� ã������ ���� �̵�
	while (1)
	{
		if (curr == minNode)						//ù��尡 �ּҳ����
		{
			huffmanTree::_head = huffmanTree::_head->next;		//��带 ��������
			break;
		}
		if (curr->next == minNode)					//���ݳ���� ������尡 �ּҳ����
			break;									//���ݳ�带 ����Ų ä�� �ݺ��� Ż��
		curr = curr->next;							//�׷��� ������ �������� �̵�
	}

	if(curr->next == minNode)						//�ּҳ�带 Ž���ؼ� �˾Ƴ´ٸ�
		curr->next = curr->next->next;				//�ּҳ�带 ����Ʈ���� ����
													//�ƴ϶�� ������ ���������Ƿ� �Ѿ

	return minNode;									//�ּҳ�� ��ȯ
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

	while (curr->left != NULL && curr->right != NULL) {			//�ڽĳ�尡 ��� NULL�̶�� ��, ���ܳ�尡 �ɶ����� �̵�
		for (int i = 0; i < curr->left->s.length(); i++) {
			if (curr->left->s.at(i) == c)						//���ʳ�忡 ã�� ���ڿ��� ������
			{
				codedText = codedText + "0";					//�������� �̵��ϹǷ� �ڵ忡 0�߰�
				direction = LEFT;								//�̵����⿡ ���� ����
				checkMove = MOVED;
			}
			
			if (i == curr->left->s.length()-1 && checkMove == NOT_YET)	//���ʳ���� ��繮�ڿ� �񱳰� ������, �̵��� ��������
			{
				codedText = codedText + "1";					//���������� �̵��ϹǷ� �ڵ忡 1�߰�
				direction = RIGHT;								//�̵����⿡ ������ ����
				checkMove = MOVED;
			}
		}
		if (direction == LEFT)									//���� �����̸�
		{
			curr = curr->left;									//�������� �̵�
			checkMove = NOT_YET;								//�����񱳸� ���� �ʱ�ȭ
		}
		else													//���� ���� �ƴϸ� ��, �������̸�
		{
			curr = curr->right;									//���������� �̵�
			checkMove = NOT_YET;								//�����񱳸� ���� �ʱ�ȭ
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

