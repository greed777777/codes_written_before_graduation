#include<string.h>
#include<fstream>
#include<cstring>
#include"node.h"
#define max_buf 999

using namespace std;

int main(int argc, char* argv[])
{
	cout << "���ϸ��� �Է��ϼ���.(��ο� Ȯ���ڱ��� ������մϴ�.)" << endl;
	char filename[256];
	cin >> filename;
	ifstream fin(filename);
	system("cls");

	if (fin.fail())												//���Ͽ��� ���н�
	{
		cout << "fileopen error!" << endl;
		system("pause");
		return 1;
	}

	string exeption[] = { "is","a","the","have","by","in","of","it","its","to","i","be","he","his" };	//����ó���� �ܾ� ����

	BinarySearchTree *bst = new BinarySearchTree;
	char str[max_buf] = { 0 };							//�� ���� �Է¹ޱ����� ���ڿ�

	int lineNum = 0;									//���° ������ Ȯ���ϱ����� ����

	char* keyword;										//�и��� �ܾ �ӽ������� ����
	char* context = NULL;								//strtok_s�� �������� �ʿ���

	while (!fin.eof())									//���� ������������ �ݺ�
	{
		fin.getline(str, sizeof(str));					//���Ͽ��� ���� �о��
		lineNum++;										//������ �о����� ���γѹ� +1
		_strlwr_s(str);									//�빮�ڸ� �ҹ��ڷ� ��ȯ

		keyword = strtok_s(str, " .,\"\'?!()-1234567890%", &context);		//{ ' ', '.' , ',','\"','\''}���� �ܾ ������ �и�

		for (int i = 0; i < sizeof(exeption) / sizeof(string); i++) //����ó���κ�
		{
			if (keyword == NULL)
				break;
			if (keyword == exeption[i])								//������ �ܾ���
				break;												//�ܾ� Ʈ���� �߰����� �ʰ� �Ѿ
			if (i == sizeof(exeption) / sizeof(string) - 1)
				bst->plus(keyword, lineNum);						//�ܾ Ʈ���� �߰�
		}


		while (keyword != NULL)							//���ٳ��������� �ݺ�
		{
			keyword = strtok_s(NULL, " .,\"\'?!()-1234567890%", &context);	//�ܾ��ϳ� �и�
			if (keyword == NULL)	break;				//�� �ܾ NULL�̸� ��, ������ �� �������� �ݺ��� Ż��

			for (int i = 0; i < sizeof(exeption) / sizeof(string); i++)
			{
				if (keyword == exeption[i])
					break;
				if (i == sizeof(exeption) / sizeof(string) - 1)
					bst->plus(keyword, lineNum);						//�ܾ Ʈ���� �߰�
			}
		}

	}
	fin.close();

	bst->Display();
	delete bst;

	system("pause");
	return 0;
}