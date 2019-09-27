#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <map>
#include <typeinfo>
#include <cmath>
#include <windows.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

vector<string> split(string input, string seperator) {
	string loop = input + seperator;
	vector<string> items;
	int p;
	while ((p = loop.find(seperator)) != -1) {
		items.push_back(loop.substr(0, p));
		loop = loop.substr(p + seperator.length());
	}
	return items;
}

int icp(char ope) {
	switch (ope) {
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 2;
	default:
		return 0;
	}
}

void doOpe(stack<long long> &nums, stack<char> &operators) {
	long long b = nums.top();
	nums.pop();
	long long a = nums.top();
	nums.pop();
	char ope = operators.top();
	operators.pop();
	switch (ope) {
	case '+':
		nums.push(a + b);
		break;
	case '-':
		nums.push(a - b);
		break;
	case '*':
		nums.push(a * b);
		break;
	case '/':
		nums.push(a / b);
		break;
	default:
		break;
	}
}

long long clumsy(int &input, int &n) {
	long long result = 0;
	stack<long long> nums;
	stack<char> operators;
	nums.push(input);
	char ope;
	for (int i = input - 1; i >= 1; i--) {
		switch (n % 4) {
		case 0:
			ope = '*';
			break;
		case 1:
			ope = '/';
			break;
		case 2:
			ope = '+';
			break;
		case 3:
			ope = '-';
			break;
		default:
			break;
		}
		n++;
		if (operators.size() == 0) {
			operators.push(ope);
		} else if (icp(operators.top()) < icp(ope)) {
			operators.push(ope);
		} else {
			while (operators.size() > 0) {
				if (icp(operators.top()) >= icp(ope)) {
					doOpe(nums, operators);
				}
				else {
					
					break;
				}
			}
			operators.push(ope);
		}
		nums.push(i);
	}
	while (operators.size() > 0) {
		doOpe(nums, operators);
	}
	return nums.top();
}


void test() {
	int input;
	int result;
	int expected;
	input = 4;
	int n = 0;
	result = clumsy(input, n);
	expected = 7;
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = 10;
	n = 0;
	result = clumsy(input, n);
	expected = 12;
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
}

void homework() {
	int input;
	int n = 0;
	cin >> input;
	int result = clumsy(input, n);
	cout << result;
}


int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}