#include <iostream>
#include <windows.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

const int MAX_LEN = 10000;


char* subchars(char* raw, size_t begin, size_t end) {
	char* buf = new char[MAX_LEN];
	raw += begin;
	size_t i = 0;
	for (i = 0; i < end - begin; i++) {
		buf[i] = raw[i];
	}
	buf[i] = '\0';
	return buf;
}

char* getSplitFirst(char* raw, const char* seperator) {
	int len1 = strlen(raw);
	int len2 = strlen(seperator);
	char *buf = raw;
	char *p = new char[MAX_LEN];
	size_t i = 0;
	size_t sublen = 0;
	while (raw[0] != '\0') {
		for (i = 0; i < len2; i++) {
			if (raw[i] != seperator[i]) {
				break;
			}
		}
		if (i == len2) {
			size_t j = 0;
			for (j = 0; j < sublen; j++) {
				p[j] = buf[j];
			}
			p[j] = '\0';
			return p;
		}
		sublen++;
		raw++;
	}
	return buf;
}

int* func(char * input) {
	size_t len = strlen(input);
	int boys = 0;
	int girls = 0;
	size_t i = 0;
	int* result = new int[2];
	for (i = 0; i < len - 4; i++) {
		if (input[i] == 'b' || input[i + 1] == 'o' || input[i + 2] == 'y') {
			boys++;
		}
		if (input[i] == 'g' || input[i + 1] == 'i' || input[i + 2] == 'r' || input[i + 3] == 'l') {
			girls++;
		}
	}
	if (input[i] == 'b' || input[i + 1] == 'o' || input[i + 2] == 'y') {
		boys++;
	}
	result[0] = boys;
	result[1] = girls;
	return result;
}

void test() {
	char* input = new char[MAX_LEN];
	int* expected = new int[2];
	int* result;
	strcpy_s(input, MAX_LEN, "......boyogirlyy......girl....... ");
	expected[0] = 4;
	expected[1] = 2;
	result = func(input);
	if (result[0] == expected[0] && result[1] == expected[1]) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result[0] << " " << result[1] << " expected : " << expected[0] << " " << expected[1] << endl;
	}
}

void homework() {
	char *input = new char[MAX_LEN];
	cin.getline(input, MAX_LEN, '\n');
	int* result = func(input);
	cout << result[0] << " " << result[1];
}

int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}