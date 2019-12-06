#include <iostream>
#include <windows.h>


#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

const int MAX_LEN = 10000;

typedef struct Transaction {
	int time;
	int amount;
	char* name;
	char* city;
}Trans;

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

//测试过没问题
Transaction parseTrans(char* raw) {
	Trans t;
	char* rest;
	t.name = strtok_s(raw, ",", &rest);
	t.time = atoi(strtok_s(rest, ",", &rest));
	t.amount = atoi(strtok_s(rest, ",", &rest));
	t.city = strtok_s(rest, ",", &rest);
	return t;
}

char* invalidTrans(char* input) {
	Trans allTrans[MAX_LEN];
	char* rest = new char[MAX_LEN];
	strcpy_s(rest, MAX_LEN + 5, input);//这里缓存+5才行，试过+2，报缓存不足
	int num = 0;
	char* temp;

	// 获取所有的订单信息
	while (rest[0] != '\0') {
		temp = getSplitFirst(rest, "\",\"");
		temp++;
		rest = strstr(rest, "\",\"");
		//strtok_s(input, "bei", &rest);
		allTrans[num] = parseTrans(temp);
		num++;
		if (rest) {
			rest += 2;
		} else {
			break;
		}
	}
	if (num==0) {
		cout << "[]";
		return 0;
	}
	allTrans[num - 1].city = subchars(allTrans[num - 1].city, 0, strlen(allTrans[num - 1].city) - 1);
	bool *flags = new bool[num] {true};
	for (size_t i = 0; i < num; i++) {
		flags[i] = true;
	}
	int finalf = 0;
	Trans t1, t2;
	for (size_t i = 0; i < num; i++) {
		t1 = allTrans[i];
		if (t1.amount < 0 || t1.amount > 1000 || t1.time < 0 || t1.time > 10000) {
			flags[i] = false;
			finalf = max(finalf, i);
		}
		for (size_t j = i + 1; j < num; j++) {
			t2 = allTrans[j];
			if (strcmp(t1.name, t2.name) == 0) {
				if (strcmp(t1.city, t2.city) != 0) {
					if (abs(t1.time - t2.time) <= 60) {
						flags[i] = false;
						flags[j] = false;
						finalf = max(finalf, j);
					}
				}
			}
		}
	}
	cout << "[";
	for (size_t i = 0; i < num; i++) {
		if (!flags[i]) {
			t1 = allTrans[i];
			cout << "\"" << t1.name << "," << t1.time << "," << t1.amount << "," << t1.city << "\"";
			if (i < finalf) {
				cout << ",";
			} else {
				break;
			}
		}
	}
	cout << "]";

	return 0;
}

void test() {
	const char* raw;
	char* input = new char[MAX_LEN];
	char* expected = new char[MAX_LEN];
	char* result = new char[MAX_LEN];
	raw = "[\"alice,20,800,mtv\",\"alice,100,1200,mtv\",\"alice,120,100,beijing\"]";
	strcpy_s(input, MAX_LEN, raw);
	raw = "[\"alice,100,1200,mtv\",\"alice,120,100,beijing\"]";
	strcpy_s(expected, MAX_LEN, raw);
	result = invalidTrans(input);
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
}

void homework() {
	char *input = new char[MAX_LEN];
	cin.getline(input, MAX_LEN, ']');
	input++;//去掉开头的'['
	invalidTrans(input);
}


int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}