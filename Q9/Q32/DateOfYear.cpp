#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <time.h>

using namespace std;

vector<string> split(string raw, string seperator) {
	string loop = raw + seperator;
	vector<string> items;
	int p;
	while ((p = loop.find(seperator)) != -1) {
		items.push_back(loop.substr(0, p));
		loop = loop.substr(p + seperator.length());
	}
	return items;
}

bool isLeapYear(int year) {
	if (year % 400 == 0) {
		return true;
	} else if (year % 100 == 0) {
		return false;
	} else if (year % 4 == 0) {
		return true;
	} else {
		return false;
	}
}

int dateOfYear(string raw) {
	int numOfDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	vector<string> items = split(raw, "-");
	int year = std::stoi(items[0]);
	int month = std::stoi(items[1]);
	int date = std::stoi(items[2]);
	int result = 0;
	if (isLeapYear(year)) {
		numOfDays[1] = 29;
	}
	for (size_t i = 0; i < month-1; i++) {
		result += numOfDays[i];
	}
	return result += date;
}

void homework() {
	string raw;
	getline(cin, raw);
	int date = dateOfYear(raw);
	cout << date;
}

void test() {
	string raw = "2018-12-31";
	int date = dateOfYear(raw);
	cout << date << endl;
	raw = "1900-3-1";
	date = dateOfYear(raw);
	cout << date << endl;
}

int main() {
	//test();
	homework();
	//system("pause");
}