#include<string.h>
#include<fstream>
#include<cstring>
#include"node.h"
#define max_buf 999

using namespace std;

int main(int argc, char* argv[])
{
	cout << "파일명을 입력하세요.(경로와 확장자까지 적어야합니다.)" << endl;
	char filename[256];
	cin >> filename;
	ifstream fin(filename);
	system("cls");

	if (fin.fail())												//파일열기 실패시
	{
		cout << "fileopen error!" << endl;
		system("pause");
		return 1;
	}

	string exeption[] = { "is","a","the","have","by","in","of","it","its","to","i","be","he","his" };	//예외처리할 단어 모음

	BinarySearchTree *bst = new BinarySearchTree;
	char str[max_buf] = { 0 };							//한 줄을 입력받기위한 문자열

	int lineNum = 0;									//몇번째 줄인지 확인하기위한 변수

	char* keyword;										//분리한 단어를 임시저장할 변수
	char* context = NULL;								//strtok_s를 쓰기위해 필요함

	while (!fin.eof())									//파일 다읽을때까지 반복
	{
		fin.getline(str, sizeof(str));					//파일에서 한줄 읽어옴
		lineNum++;										//한줄을 읽었으니 라인넘버 +1
		_strlwr_s(str);									//대문자를 소문자로 변환

		keyword = strtok_s(str, " .,\"\'?!()-1234567890%", &context);		//{ ' ', '.' , ',','\"','\''}으로 단어를 구분후 분리

		for (int i = 0; i < sizeof(exeption) / sizeof(string); i++) //예외처리부분
		{
			if (keyword == NULL)
				break;
			if (keyword == exeption[i])								//예외인 단어라면
				break;												//단어 트리에 추가하지 않고 넘어감
			if (i == sizeof(exeption) / sizeof(string) - 1)
				bst->plus(keyword, lineNum);						//단어를 트리에 추가
		}


		while (keyword != NULL)							//한줄끝날때까지 반복
		{
			keyword = strtok_s(NULL, " .,\"\'?!()-1234567890%", &context);	//단어하나 분리
			if (keyword == NULL)	break;				//그 단어가 NULL이면 즉, 한줄이 다 읽혔으면 반복문 탈출

			for (int i = 0; i < sizeof(exeption) / sizeof(string); i++)
			{
				if (keyword == exeption[i])
					break;
				if (i == sizeof(exeption) / sizeof(string) - 1)
					bst->plus(keyword, lineNum);						//단어를 트리에 추가
			}
		}

	}
	fin.close();

	bst->Display();
	delete bst;

	system("pause");
	return 0;
}