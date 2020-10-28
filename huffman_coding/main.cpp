#pragma once
#include<iostream>
#include<string>
#include<fstream>

#include"Tree.h"

using namespace std;

unsigned char MyPow(char a, char b);
unsigned char MyLog2(unsigned char num);
void PresentCode(huffmanTree &root);
string ReplaceString(string subject, const string &search, const string &replace);

int main(void)
{
	char selMode;
	string fileName;
	cout << "���α׷� ��带 �����ϼ���." << endl;
	cout << "1. ������ \n2. �������" << endl;
	cin >> selMode;
	system("cls");
	
	if (selMode == '1')															//������
	{
		string treeName;
		cout << "������ �ؽ�Ʈ������ �̸��� Ȯ���ڸ���� �Է����ּ���." << endl;
		cin >> fileName;
		system("cls");
		treeName = ReplaceString(fileName, ".txt", "_Tree.txt");

		huffmanTree Root;
		ifstream fin(fileName);
		if (fin.fail())
		{
			cout << "���Ͽ��� ����" << endl;
			system("pause");

			return 1;
		}

		//���� �ؽ�Ʈ���Ϸκ��� �ܾ��� ����Ƚ���� ����� _tree.txt������ �����մϴ�.
		cout << "Ʈ������ ������..." << endl;

		ofstream fout(treeName);
		char character;

		while (!fin.eof())
		{
			fin.get(character);
			Root.InsertList(character);
		}

		Root.FPrintTree(fout);
		Root.PlantTreeFrom();
		fin.close();
		fout.close();
		
		cout << "Ʈ������ �����Ϸ�" << endl;

		Root.PrintTree();

		system("pause");
		system("cls");

		//�������Ϸκ��� 1�� 0���θ��� �ӽ��ؽ�Ʈ������ �����մϴ�.
		
		cout << "�ӽ����� ������..." << endl;

		cout << endl << endl << endl;
		PresentCode(Root);
		
		fin.open(fileName);
		

		fout.open("temp.txt");
		ifstream cursor;
		cursor.open("text.txt");
		cursor.seekg(0, ios::end);
		while (fin.tellg() != cursor.tellg())
		{
			fin.get(character);

			if (character == EOF)
				break;
			else if (character == '\t')
				break;
			else
				fout << Root.Encoding(character);

		}

		fin.close();
		fout.close();
		cursor.close();

		cout << "�ӽ����� ����Ϸ�" << endl;
		system("cls");
		


		//--------------------------------------------------------------------------------

		//-----------------------------------------------�ӽ��ؽ�Ʈ���Ϸκ��� ���̳ʸ����� ����

		cout << "���� ������..." << endl;

		string binFileName;
		binFileName = ReplaceString(fileName, ".txt", ".bin");
		fin.open("temp.txt");
		fout.open(binFileName, ios::out | ios::binary);
		char codedText;
		char binaryValue;
		unsigned char uc_binaryValue;
		char extra;
		unsigned char uc_extra;
		while (!fin.eof()) {
			uc_binaryValue = 0;
			for (int i = 0; i < 8; i++) {
				fin.get(codedText);
				if (fin.eof()) {
					uc_extra = MyPow(2, 8 - i);
					extra = uc_extra;
					break;
				}
				codedText = codedText - '0';						//���ڷλ���ϱ����� �ƽ�Ű������
				uc_binaryValue += MyPow(2, (7 - i)) * codedText;	//������������ �����ڸ��� ���
			}
			binaryValue = uc_binaryValue;
			fout.write(&binaryValue, sizeof(char));
		}

		fout.write(&extra, sizeof(char));							//���������� ���������� ���

		fout.close();
		fin.close();

		const char* command;
		string com;
		com = "del ";
		com = com + fileName;
		command = com.c_str();

		cout << "�������� ����" << endl;
		system(command);

		cout << "�ӽ����� ����" << endl;
		system("del temp.txt");

		system("cls");

		cout << "Compress Success" << endl;


	}
	else if (selMode == '2')										//�������
	{
		cout << "������ ���������� �̸��� Ȯ���ڸ���� �Է����ּ���." << endl;
		cin >> fileName;
		system("cls");


		ifstream fin;
		ofstream fout;
		char extra1;
		char binaryValue1;
		fin.open(fileName);

		if (fin.fail())
		{
			cout << "������ �������� �ʽ��ϴ�." << endl;
			system("pause");

			return 1;
		}
		char checkFile;
		ifstream fileSize;
		fileSize.open(fileName);
		fileSize.seekg(0,ios::end);
		fin.read(&checkFile, sizeof(char));

		//-------------------------------------------�������� ���
		if (checkFile == 0) {
			fin.read(&checkFile, sizeof(char));
			if (checkFile == 0)
				if (fin.tellg() == fileSize.tellg()) {
					string newFile;
					newFile = ReplaceString(fileName, ".bin", "_D.txt");
					string treeName;
					treeName = ReplaceString(fileName, ".bin", "_Tree.txt");
					fout.open(newFile);
					
					fin.close();
					fileSize.close();
					fout.close();
					
					const char* command;
					string com;
					com = "del ";
					com = com + fileName;
					command = com.c_str();

					system(command);

					com = "del ";
					com = com + treeName;
					command = com.c_str();

					system(command);


					cout << "Decompress Success" << endl;

					system("pause");
					return 0;
				}
		}
		fin.close();
		fileSize.close();

		//---------------------------------------------�ؽ�Ʈ���Ϸκ��� Ʈ�� �����

		huffmanTree Root;
		string treeName;
		treeName = ReplaceString(fileName, ".bin", "_Tree.txt");
		fin.open(treeName);

		if (fin.fail()) {
			cout << "Tree������ ���� ���������� �����߽��ϴ�." << endl;
			system("pause");
			return 2;
		}

		char character;
		char tab;
		char num = '0';
		int maxit;
		string apearNumber = "";

		cout << "Ʈ�� ������..." << endl;
		while (!fin.eof())
		{
			fin.get(character);
			fin.get(tab);

			while (num != '\t') {
				fin.get(num);
				apearNumber = apearNumber + num;
				if (fin.eof())
					break;
			}

			maxit = stoi(apearNumber);

			for (int i = 0; i < maxit; i++)
				Root.InsertList(character);
			num = '0';
			apearNumber = "";
			if (fin.eof())
				break;
		}

		Root.PlantTreeFrom();
		cout << "Ʈ������ �Ϸ�" << endl;

		fin.close();

		//---------------------------------------------------------------------------------------
		//--------------------------------------------------------------���������� �ӽ����Ϸ� ����

		unsigned char uc_extra1;
		unsigned char uc_binaryValue1;
		//string temp;
		fin.open(fileName, ios::binary | ios::in);
		//temp = ReplaceString(fileName, ".bin", "_Dtemp.txt");
		fout.open("temp.txt");
		ifstream search(fileName, ios::binary | ios::in);
		search.seekg(-1, ios::end);
		search.read(&extra1, sizeof(char));
		search.close();
		search.open(fileName, ios::binary | ios::in);
		if (extra1 != 0)
			search.seekg(-2, ios::end);
		else												
			search.seekg(-3, ios::end);

		cout << "�ӽ����� ������..." << endl;

		while (!fin.eof()) {
			fin.read(&binaryValue1, sizeof(char));
			uc_binaryValue1 = binaryValue1;

			for (int j = 0; j < 8; j++)
			{
				if (uc_binaryValue1 - MyPow(2, (7 - j)) >= 0)
				{
					uc_binaryValue1 = uc_binaryValue1 - MyPow(2, (7 - j));
					fout << "1";
				}
				else
					fout << "0";
			}

			if (fin.tellg() == search.tellg())
				break;

		}
		fin.close();

		fin.open(fileName, ios::binary | ios::in);
		if (extra1 != 0)
		{
			fin.seekg(-2, ios::end);
			fin.read(&binaryValue1, sizeof(char));
			uc_binaryValue1 = binaryValue1;
			extra1 = MyLog2(extra1);

			for (int i = 0; i < 8 - extra1; i++)
			{
				if (uc_binaryValue1 - MyPow(2, (7 - i)) >= 0)
				{
					uc_binaryValue1 = uc_binaryValue1 - MyPow(2, (7 - i));
					fout << "1";
				}
				else
					fout << "0";
				if (7 - i == extra1)
					break;
			}
		}
		else
		{
			fin.seekg(-3, ios::end);
			fin.read(&binaryValue1, sizeof(char));
			uc_binaryValue1 = binaryValue1;

			for (int i = 0; i < 8; i++)
			{
				if (uc_binaryValue1 - MyPow(2, 7 - i) >= 0)
				{
					uc_binaryValue1 = uc_binaryValue1 - MyPow(2, (7 - i));
					fout << "1";
				}
				else
					fout << "0";
			}
		}

		cout << "�ӽ����� ����Ϸ�" << endl;
		system("cls");

		fin.close();
		fout.close();
		search.close();
		
		
		//---------------------------------------------------------------------------------------

		fin.open("temp.txt");
		string originalFile;
		originalFile = ReplaceString(fileName, ".bin", "_D.txt");
		fout.open(originalFile);
		char direction;
		Node* curr;

		cout << "���� ������..." << endl;
		while (!fin.eof())
		{
			curr = Root.ReturnRoot();
			//cout << "new char decompressing" << endl;
			while (curr->left != NULL && curr->right != NULL)
			{
				fin.get(direction);
				if (direction == '1')
					curr = curr->right;
				else
					curr = curr->left;

				if (curr->left == NULL && curr->right == NULL)
					fout << curr->s;

				if (fin.eof())
					break;
			}

		}

		fin.close();
		fout.close();

		const char* command;
		string com;
		com = "del ";
		com = com + fileName;
		command = com.c_str();

		cout << "�������� ����" << endl;
		system(command);

		com = "del ";
		com = com + treeName;
		command = com.c_str();

		cout << "�ӽ����� ����" << endl;
		system(command);
		
		system("del temp.txt");

		system("cls");

		cout << "Decompress Success" << endl;


	}
	else
	{
		cout << "�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�." << endl;
		system("pause");
		return -1;
	}

	
	::system("pause");

	return 0;
}

unsigned char MyPow(char a, char b) {
	unsigned char pow = 1;
	for (int i = 0; i < b; i++)
		pow = pow * a;
	return pow;
}

unsigned char MyLog2(unsigned char num) {
	unsigned char count=0;
	while (num  >= 2) {
		num = num / 2;
		count++;
	}

	return count;
}

string ReplaceString(string subject, const string &search, const string &replace) {
	size_t pos = 0;
	while (((pos = subject.find(search, pos)) != string::npos)) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}

	return subject;
}

void PresentCode(huffmanTree &root) {
	char c;

	for (c = 'a'; c < 'z'; c++)
	{
		cout << c << ": " << root.Encoding(c) << endl;
	}

	cout << endl << endl << endl;

	for (c = 'A'; c < 'Z'; c++)
	{
		cout << c << ": " << root.Encoding(c) << endl;
	}	
}