//boj10799 : �踷�� �ڸ��� //��ø��ȣ ����
#include<iostream>
#include<stack>

using namespace std;

stack<char> s;
int stick = 0;
int mcount;

int main(void) {
	string input;
	mcount = 0;
	cin >> input;

	for (int i = 0; i < input.size(); i++) {

		if (input.at(i) == '(') {//���°�ȣ �϶��� ������ Ǫ��
			//s.push(input.at(i));
			stick++;
		}
		else {//�ݴ°�ȣ�϶��� �տ� �� Ȯ��
			if (input.at(i - 1) == '(') {//�տ� ���� ���°�ȣ��� �̰� ��������
				//��ø�� ��������ŭ ������ +1
				//�׷��� �ٷξ��� ���°�ȣ�� ������ �ݴ°�ȣ�� �����̷� �������̹Ƿ� ����-1
				stick--;
				mcount = mcount + stick;
				//s.pop();
			}
			else {//�տ����� �ݴ°�ȣ��� �������� ������. �����̴� mcount +1����.
				stick--;
				mcount++;
			}
		}
		
	}
	cout << mcount;
}