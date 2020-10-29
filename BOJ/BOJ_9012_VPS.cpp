#include<iostream>
#include<stack>
#include<string>
#include<queue>

using namespace std;

int main(void) {
	stack<char> s;
	int num,origin;
	char input;
	int size;

	const char* answer[100];

	cin >> num;
	origin = num;
	string line;

	for(int i = 0; i < origin; i++){
		cin >> line;
		size = line.length();

		for (int j = 0; j < size; j++) {
			input = line.at(j);

			if (input == '(') {
				s.push(input);
			}
			else {
				if (s.empty() == true)
				{
					s.push(')');
					break;
				}
				else
					s.pop();
			}
		}
		
		answer[i] = (s.empty() ? "YES" : "NO");
		line.clear();
		while (false == s.empty()) {
			s.pop();
		}
	}

	for (int i = 0; i < origin; i++) {
		cout << answer[i] << endl;
	}
}