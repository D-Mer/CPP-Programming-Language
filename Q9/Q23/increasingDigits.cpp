#include <iostream>
#include <string>
#include <vector>


//#define foreach(i, set) \
//		for (decltype(set.begin()) i = set.begin();it != set.end(); i++)
using namespace std;


int checkBefore(int p, string chars) {
	if (p == chars.length()) {
		return p;
	}
	while (p > 1) {
		if (chars.at(p - 2) == chars.at(p - 1)) {
			p--;
		}
		else {
			break;
		}
	}
	return p;
}

int getDropPos(string chars) {
	int len = chars.length();
	char before = chars.at(0);
	char c;
	int i = 1;
	for (i; i < len; i++) {
		c = chars.at(i);
		if (c < before) {
			break;
		}
		before = c;
	}
	return checkBefore(i, chars);
}

string decrease(int p, string chars) {
	string result = chars.substr(0, p - 1) + (char)(chars.at(p - 1) - 1);
	for (int i = p; i < chars.length(); i++) {
		result += "9";
	}
	return result;
}

void cut0(string &chars) {
	for (int i = 0; i < chars.length() - 1; i++) {
		if (chars.at(i) == '0') {
			chars = chars.substr(1);
		}
		else {
			break;
		}
	}
}

string increaseDig(string chars) {
	int p = getDropPos(chars);
	int len = chars.length();
	if (p == len) {
		return chars;
	}
	string result = decrease(p, chars);
	cut0(result);
	return result;

}

string monotoneIncreasingDigits(int N) {
	vector<int> vec;

	while (N > 0)
	{
		vec.push_back(N % 10);
		N /= 10;
	}

	for (int i = vec.size() - 1; i > 0; i--)
	{
		if (vec[i] > vec[i - 1])
		{
			while (i < vec.size() - 1 && vec[i] == vec[i + 1])
			{
				i++;
			}
			vec[i]--;
			for (int j = i - 1; j >= 0; j--)
			{
				vec[j] = 9;
			}
			break;
		}
	}
	for (int i = vec.size() - 1; i >= 0; i--)
	{
		N *= 10;
		N += vec[i];
	}
	return to_string(N);
}

void test() {
	string s1;
	string s2;
	for (int i = 0; i < 10000; i++) {
		s1 = increaseDig(to_string(i));
		s2 = monotoneIncreasingDigits(i);
		if (s1 != s2) {
			cout << i << " error: s1=" << s1 << " while s2=" << s2 << endl;
		}
		//system("pause");
	//}

	}
	cout << "end";
	system("pause");
}

void homework() {
	string input;
	cin >> input;
	string result = increaseDig(input);
	cout << result;
	//system("pause");
}

int main() {
	//test();
	homework();
	//system("pause");
}

