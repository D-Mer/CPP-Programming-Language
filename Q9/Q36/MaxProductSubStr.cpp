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

string maxProductSubStr(string input) {
	vector<string> items = split(input, " ");
	long long item;
	long long max_value = stoll(items[0]);
	long long current = 1;
	int start = 0, end = 0;
	for (size_t i = 0; i < items.size(); i++) {
		for (size_t j = i; j < items.size(); j++) {
			current *= stoll(items[j]);
			if (current == max_value) {
				if (end - start < j - i) {
					start = i;
					end = j;
				}
			} else if (current > max_value) {
				max_value = current;
				start = i;
				end = j;
			}
		}
		current = 1;
	}
	string result = "[";
	if (max_value <= 0) {
		for (size_t i = 0; i < items.size() - 1; i++) {
			result += items[i] + ",";
		}
	} else {
		for (size_t i = start; i < end; i++) {
			result += items[i] + ",";
		}
	}
	return result + items[end] + "]";
}

//string maxProductSubStr(string input) {
//	vector<string> items = split(input, " ");
//	long long item;
//	long long current_pos = 1;
//	long long current_neg = 1;
//	long long max_value = stoll(items[0]);
//	long long temp_value, temp_start;
//	int current_pos_start = 0;
//	int current_neg_start = 0;
//	int max_start = 0, max_end = 0;
//	for (size_t i = 1; i < items.size(); i++) {
//		item = stoll(items[i]);
//		temp_value = current_pos;
//		current_pos *= item;
//		if (current_pos < 1) {
//
//		}
//		current_neg *= item;
//		
//
//		if (current_pos >= max_value) {
//			max_start = current_pos_start;
//			max_end = i;
//			max_value = current_pos;
//		}
//		if (current_neg >= max_value) {
//			max_start = current_neg_start;
//			max_end = i;
//			max_value = current_neg;
//		}
//		if (current_pos < 1) {
//			current_pos = 1;
//			current_pos_start = i + 1;
//		}
//		if (current_neg > -1) {
//			current_neg = 1;
//			current_neg_start = i + 1;
//		}
//	}
//	if (max_value == 0) {
//		return "[" + input + "]";
//	}
//	string result = "";
//	result += "[";
//	for (size_t i = max_start; i < max_end; i++) {
//		result += items[i] + ",";
//	}
//	result += items[max_end];
//	return result + "]";
//}

void test() {
	string input;
	string result;
	string expected;
	input = "1 -3 5 9";
	result = maxProductSubStr(input);
	expected = "[5,9]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "-1 0 -1";
	result = maxProductSubStr(input);
	expected = "[-1,0,-1]";
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
}

void homework() {
	string input;
	getline(cin, input);
	getline(cin, input);
	string result = maxProductSubStr(input);
	cout << result;
	//system("pause");
}


int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}