#include<iostream>
#include<string>

using namespace std;

struct ListNode {
	int line;
	ListNode *next;
};

class linkedlist {
public:
	ListNode *_head;

	linkedlist()
	{
		_head = NULL;
	}

	void printline()
	{
		ListNode *curr = NULL;
		if (_head)
			curr = _head;
		while (curr)
		{
			cout << curr->line << " ";
			curr = curr->next;
		}
		cout << endl;
	}

	void addline(int num)
	{
		ListNode *node = new ListNode;
		node->line = num;
		node->next = NULL;

		ListNode *parent = NULL;
		ListNode *curr = NULL;

		if (_head == NULL) _head = node;
		else
		{
			curr = _head;
			while (curr)
			{
				parent = curr;								//부모노드 선정
				curr = curr->next;
			}
			parent->next = node;
		}
	}
};

struct Node
{
	Node *left;
	Node *right;
	string data;
	linkedlist *line;
};

class BinarySearchTree
{
public:
	Node *_root;

	BinarySearchTree()
	{
		_root = NULL;
	}

	~BinarySearchTree()
	{
		Free_node(_root);
	}

	void Store(const char *a, int line);
	void In_order(Node *node);
	void Display();
	void Free_node(Node *leaf);
	Node* search(const char *keyword);
	void plus(const char *a, int line);
};

void BinarySearchTree::plus(const char *a, int line)
{
	if (this->search(a) == NULL)
		this->Store(a, line);
	else
		search(a)->line->addline(line);
}


void BinarySearchTree::Store(const char *a, int line)
{

	Node *node = new Node;
	node->data = a;
	node->left = NULL;
	node->right = NULL;
	node->line = new linkedlist;
	node->line->addline(line);

	Node *parent = NULL;
	Node *curr = NULL;

	if (_root == NULL) _root = node;
	else
	{
		curr = _root;
		while (curr)
		{
			parent = curr;								//부모노드 선정
			if (node->data.compare(curr->data) > 0)		//비교 결과 0보다 크면, 즉 새로운 데이터가 curr 데이터보다 알파벳 후순이면
				curr = curr->right;						//오른쪽으로
			else
				curr = curr->left;						//아니면 왼쪽으로
		}
		if (node->data.compare(parent->data) < 0)			//추가할노드와 부모노드 비교후 새로운 노드가  앞순이면
			parent->left = node;						//왼쪽에 노드추가
		else
			parent->right = node;						//아니면 오른쪽에 노드추가
	}
};

void BinarySearchTree::Free_node(Node *leaf)
{
	if (leaf)
	{
		if (leaf->left) Free_node(leaf->left);
		if (leaf->right) Free_node(leaf->right);
		delete leaf;
	}
}

void BinarySearchTree::In_order(Node *p)
{
	if (p)
	{
		if (p->left)
			In_order(p->left);
		cout.width(15);
		cout.setf(ios::left);
		cout << p->data << "\t";
		p->line->printline();
		if (p->right)
			In_order(p->right);
	}
	else
		return;
}

void BinarySearchTree::Display()
{
	cout.width(15);
	cout.setf(ios::left);
	cout << "단어" << '\t' << "라인 번호" << endl;
	In_order(_root);
}

Node* BinarySearchTree::search(const char *keyword)
{
	Node *target = NULL;
	Node *parent = NULL;
	target = _root;

	while (target)
	{
		parent = target;
		if (target->data.compare(keyword) < 0)
			target = target->right;
		else if (target->data.compare(keyword) > 0)
			target = target->left;
		else if (target->data == keyword)
		{
			return target;
		}
	}
	return NULL;
}
