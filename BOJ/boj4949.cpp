#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main(void) {
	string input;
	
	bool complete;
	stack<char> s;
	//cin.getline(line, 101);

	getline(cin, input);
	

	complete = true;

	while (input!=".") {

		for (unsigned int i = 0; input.at(i)!='.'; i++) {
			if (input.at(i) == '(') {
				s.push('(');
			}
			else if (input.at(i) == ')') {
				if (s.size() == 0) {
					complete = 0;
					break;
				}
				else if (s.top() == '(') {
					s.pop();
					continue;
				}
				else {
					complete = 0;
					break;
				}
			}
			else if (input.at(i) == '[') {
				s.push('[');
			}
			else if (input.at(i) == ']') {
				if (s.size() == 0) {
					complete = 0;
					break;
				}
				else if (s.top() == '[') {
					s.pop();
					continue;
				}
				else {
					complete = 0;
					break;
				}
			}
		}

		if (s.size() != 0)//스택 안비었으면
			complete = false;

		if (complete) {
			cout << "yes" << endl;
		}
		else
			cout << "no" << endl;

		getline(cin, input);

		while (s.size() != 0)
			s.pop();
		complete = 1;
	}
}