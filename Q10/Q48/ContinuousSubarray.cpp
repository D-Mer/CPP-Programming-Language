#include <iostream>
#include <windows.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

const int MAX_LEN = 10000;

char* subchars(const char* raw, const size_t begin, const size_t end) {
	size_t maxlen = strlen(raw);
	char* buf = new char[maxlen];
	raw += begin;
	size_t i = 0;
	for (i = 0; i < end - begin; i++) {
		buf[i] = raw[i];
	}
	buf[i] = '\0';
	return buf;
}

char** splitchars(const char* raw, const char* seperator, const size_t maxsublen) {
	int p = 0;//截了几段的计数
	int rawlen = strlen(raw);
	int seplen = strlen(seperator);
	int maxsubnum = rawlen / seplen + 3;
	char** result = new char*[maxsubnum];
	const char* buf = raw;
	for (size_t i = 0; i < maxsubnum; i++) {
		result[i] = new char[maxsublen];
	}
	size_t i = 0;//和分隔符比较的计数
	size_t currentlen = 0;//当前段的长度
	while (*buf != '\0' || strlen(buf) > seplen) {
		//循环匹配，如果退出时i==len2则说明匹配成功
		for (i = 0; i < seplen; i++) {
			if (buf[i] != seperator[i]) {
				break;
			}
		}
		if (i == seplen) {
			//复制截出的一段并保存
			size_t j = 0;
			for (j = 0; j < currentlen; j++) {
				result[p][j] = raw[j];
			}
			result[p][j] = '\0';

			//初始化滑动变量
			buf += seplen;
			raw = buf;
			p++;
			currentlen = 0;
		} else {//否则继续前进
			buf++;
			currentlen++;
		}
	}
	if (*raw) {
		for (i = 0; i < strlen(raw); i++) {
			result[p][i] = raw[i];
		}
		result[p][i] = '\0';
		result[p + 1] = '\0';
	} else {
		result[p] = '\0';
	}
	return result;
}

int func(char* input, int cdt) {
	char** rawNums = splitchars(input, " ", 10);
	int n = 0;
	int nums[1000];
	while (rawNums[n]) {
		nums[n] = atoi(rawNums[n]);
		n++;
	}
	int result = 0;
	int max_n = nums[0];
	int min_n = nums[0];
	bool flag = false;
	for (int i = 0; i < n; i++) {
		max_n = nums[i];
		min_n = nums[i];
		for (int j = i + 1; j < n; j++) {
			if (nums[j] > max_n) {
				max_n = nums[j];
				flag = true;
			} else if (nums[j] < min_n) {
				min_n = nums[j];
				flag = true;
			}
			if (flag) {
				if (max_n - min_n > cdt) {
					result += n - j;
					flag = false;
					break;
				}
				flag = false;
			}
		}
	}
	return result;
}

void test() {
	char* input = new char[MAX_LEN];
	int expected = 6;
	strcpy_s(input, MAX_LEN, "3 6 4 3 2");
	int result = func(input, 2);
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	strcpy_s(input, MAX_LEN, "1 3 2 6");
	expected = 1;
	result = func(input, 2);
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
}

void homework() {
	char *input = new char[MAX_LEN];
	int cdt;
	cin.getline(input, MAX_LEN, '\n');
	cin >> cdt;
	int result = func(input, cdt);
	cout << result;
}

int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}