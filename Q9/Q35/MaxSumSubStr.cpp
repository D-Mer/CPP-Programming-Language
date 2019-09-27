#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <typeinfo>
#include <cmath>

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

string maxSumSubStr(string input) {
	vector<string> items = split(input.substr(1, input.length() - 2), ",");
	long long x;
	long long maxItem = stoll(items[1]);
	for (size_t i = 2; i < items.size(); i++) {
		if (stoll(items[i]) > maxItem) {
			maxItem = stoll(items[i]);
		}
	}
	long long currentMax = 0;
	long long max = 0;
	int start = 1;
	int r_start = 1, r_end = 1;
	string result = "";
	for (size_t i = 1; i < items.size(); i++) {
		x = stoll(items[i]);
		currentMax += x;
		if (currentMax < 0) {
			currentMax = 0;
			start = i + 1;
		} else if (currentMax > max) {
			r_start = start;
			r_end = i;
			max = currentMax;
		}
	}
	if (max <= 0) {
		return to_string(maxItem);
	}
	for (size_t i = r_start; i < r_end; i++) {
		result += items[i] + ",";
	}
	result += items[r_end];
	return result;
}

long long getSum(string sub) {
	vector<string> items = split(sub, ",");
	long long result = 0;
	if (items[0] == "") {
		return result;
	}
	for (size_t i = 0; i < items.size(); i++) {
		result += stoll(items[i]);
	}
	return result;
}

void homework() {
	string input;
	getline(cin, input);
	string sub = maxSumSubStr(input);
	long long result = getSum(sub);
	cout << result;
}

void test() {
	string input = "[9,-2,1,-3,4,-1,2,1,-5,4] ";
	string sub = maxSumSubStr(input);
	long long sum;
	if (sub == "4,-1,2,1") {
		if ((sum = getSum(sub)) == 6) {
			cout << "pass" << endl;
		} else {
			cout << "sum error : " << sum << " expected : 6" << endl;
		}
	} else {
		cout << "sub str error : " << sub << " expected : 4,-1,2,1" << endl;
	}
	input = "[4, 2147483647, 2147483647, 2147483647, 2147483647]";
	sub = maxSumSubStr(input);
	sum = getSum(sub);
	if ((sum = getSum(sub)) == 8589934588) {
		cout << "pass" << endl;
	} else {
		cout << "sum error : " << sum << " expected : 8589934588" << endl;
	}
	input = "[4, 2147483647, -2147483648, 2147483647, -2147483648]";
	sub = maxSumSubStr(input);
	sum = getSum(sub);
	if ((sum = getSum(sub)) == 2147483647) {
		cout << "pass" << endl;
	} else {
		cout << "sum error : " << sum << " expected : 2147483647" << endl;
	}
	input = "[2,-2,-1]";
	sub = maxSumSubStr(input);
	sum = getSum(sub);
	if ((sum = getSum(sub)) == -1) {
		cout << "pass" << endl;
	} else {
		cout << "sum error : " << sum << " expected : -1" << endl;
	}
	input = "[3,30,37,38]";
	sub = maxSumSubStr(input);
	sum = getSum(sub);
	if ((sum = getSum(sub)) == 105) {
		cout << "pass" << endl;
	} else {
		cout << "sum error : " << sum << " expected : 105" << endl;
	}
	input = "[4, 2147483647, -2147483648, 2147483647, 2147483647]";
	sub = maxSumSubStr(input);
	sum = getSum(sub);
	if ((sum = getSum(sub)) == 4294967294) {
		cout << "pass" << endl;
	} else {
		cout << "sum error : " << sum << " expected : 4294967294" << endl;
	}
	input = "[28, 48, 45, 14, 44, 6, -28, -19, -45, 1, -24, -26, -47, 13, 6, 39, -37, -23, 35, -34, -50, -19, -42, 34, -22, 16, -42, 43, -38]";
	sub = maxSumSubStr(input);
	sum = getSum(sub);
	if ((sum = getSum(sub)) == 157) {
		cout << "pass" << endl;
	} else {
		cout << "sum error : " << sum << " expected : 157" << endl;
	}
	cout << "done!" << endl;
}

int main() {
	//test();
	homework();
	//system("pause");
}