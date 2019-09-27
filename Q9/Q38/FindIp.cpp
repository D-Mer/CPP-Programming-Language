#include <iostream>
#include <string>
#include <vector>
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

void recursive(int n, string ip, string str, vector<string> &IPs) {
	if (n == 4) {
		if (str.empty()) {
			IPs.push_back(ip);
		}
		return;
	} else {
		for (size_t i = 1; i < 4; i++) {
			if (str.length() < i) {
				return;
			}
			if (stoi(str.substr(0, i)) > 255 || to_string(stoi(str.substr(0, i))) != str.substr(0, i)) {
				continue;
			} else {
				recursive(n + 1, ip + str.substr(0, i) + ".", str.substr(i), IPs);
			}
		}
	}
}

string findIP(string input) {
	vector<string> IPs;
	recursive(0, "", input, IPs);
	string result = "[";
	for (size_t i = 0; i < IPs.size() - 1; i++) {
		result += "\"" + IPs[i].substr(0, IPs[i].length() - 1) + "\",";
	}
	result += "\"" + IPs[IPs.size() - 1].substr(0, IPs[IPs.size() - 1].length() - 1) + "\"]";
	return result;
}

void test() {
	string input;
	string result;
	string expected;
	input = "0000";
	result = findIP(input);
	expected = "[\"0.0.0.0\"]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "25525511135";
	result = findIP(input);
	expected = "[\"255.255.11.135\",\"255.255.111.35\"]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "25525511135";
	result = findIP(input);
	expected = "[\"255.255.11.135\",\"255.255.111.35\"]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "010010";
	result = findIP(input);
	expected = "[\"255.255.11.135\",\"255.255.111.35\"]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "106820214";
	result = findIP(input);
	expected = "[\"255.255.11.135\",\"255.255.111.35\"]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "101010100";
	result = findIP(input);
	expected = "[\"255.255.11.135\",\"255.255.111.35\"]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
}

void homework() {
	string input;
	cin >> input;
	int result = split(findIP(input), ",").size();
	cout << result;
}


int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}