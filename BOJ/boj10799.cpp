//boj10799 : 쇠막대 자르기 //중첩괄호 세기
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

		if (input.at(i) == '(') {//여는괄호 일때는 무조건 푸시
			//s.push(input.at(i));
			stick++;
		}
		else {//닫는괄호일때는 앞에 것 확인
			if (input.at(i - 1) == '(') {//앞에 것이 여는괄호라면 이건 레이저임
				//중첩된 파이프만큼 파이프 +1
				//그런대 바로앞의 여는괄호는 지금의 닫는괄호와 쌍을이뤄 레이저이므로 막대-1
				stick--;
				mcount = mcount + stick;
				//s.pop();
			}
			else {//앞에것이 닫는괄호라면 파이프의 말단임. 말단이니 mcount +1해줌.
				stick--;
				mcount++;
			}
		}
		
	}
	cout << mcount;
}