#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string line) {
	int front = 0;
	int tail = line.length() - 1;
	while (tail - front >= 0) {
		if (line.at(front) == line.at(tail)) {
			front++;
			tail--;
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

string getLongestPalindrome(string input) {
	int len = input.length();
	int head = 0;
	int tail = len - 1;
	string longest = input.substr(0, 1);
	string temp;
	int front;
	int back;
	for (int i = 0; i < len; i++) {
		for (int j = longest.length() + 1; i + j <= len; j++) {
			temp = input.substr(i, j);
			if (isPalindrome(temp)) {
				longest = temp;
			}
		}
	}
	return longest;
}

void test() {
	string s1 = "aykskksya";
	string expected = "skks";
	string s2 = getLongestPalindrome(s1);
	if (expected == s2) {
		cout << "right";
	}
	else {
		cout << "error : " << s2 << " , expected : " << expected;
	}
	system("pause");
}

void homework() {
	string input;
	cin >> input;
	string result = getLongestPalindrome(input);
	cout << result;
	//system("pause");
}

int main() {
	//test();
	homework();
	//system("pause");
}