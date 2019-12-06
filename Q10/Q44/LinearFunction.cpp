#include <iostream>
#include <windows.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

const int MAX_LEN = 100;

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

char** splitchars(const char* raw, const char* seperator, const size_t maxlen) {
	int p = 0;//截了几段的计数
	char** result = new char*[maxlen];
	for (size_t i = 0; i < maxlen; i++) {
		result[i] = new char[maxlen];
	}
	int len1 = strlen(raw);
	int len2 = strlen(seperator);
	char* rest = new char[maxlen];//当前剩余部分，流每匹配到一段才切割一次
	char* buf = new char[maxlen];//用来滑动对比的流
	strcpy_s(rest, maxlen + 5, raw);
	strcpy_s(buf, maxlen + 5, raw);
	char *partResult = new char[MAX_LEN];//记录当前截出一段
	size_t i = 0;//和分隔符比较的计数
	size_t sublen = 0;//当前段的长度
	while (buf[0] != '\0' || strlen(buf) >= len2) {
		//循环匹配，如果退出时i==len2则说明匹配成功
		for (i = 0; i < len2; i++) {
			if (buf[i] != seperator[i]) {
				break;
			}
		}
		if (i == len2) {
			//复制截出的一段并保存
			size_t j = 0;
			for (j = 0; j < sublen; j++) {
				partResult[j] = rest[j];
			}
			partResult[j] = '\0';
			strcpy_s(result[p], maxlen + 5, partResult);

			//初始化滑动变量
			buf += len2;
			rest = buf;
			p++;
			sublen = 0;
		} else {//否则继续前进
			buf++;
			sublen++;
		}
	}
	if (strlen(rest)) {
		result[p] = rest;
		result[p + 1] = '\0';
	} else {
		result[p] = '\0';
	}
	return result;
}

inline int gcd(int a, int b) {
	int a2 = max(abs(a),abs(b));
	int b2 = min(abs(a), abs(b));
	int q = a2 / b2;
	int r = a2 % b2;
	return r == 0 ? b2 : gcd(b2, r);
}

void func(char* input1, char* input2) {
	char** rawPoint = splitchars(subchars(input1, 1, strlen(input1 - 1)), ",", 10);
	int* point1 = new int[2] {atoi(rawPoint[0]), atoi(rawPoint[1])};
	rawPoint = splitchars(subchars(input2, 1, strlen(input2 - 1)), ",", 10);
	int* point2 = new int[2] {atoi(rawPoint[0]), atoi(rawPoint[1])};
	int xd = point1[0] - point2[0];
	int yd = point1[1] - point2[1];
	if (yd == 0) {
		cout << "y=" << point1[1];
	}
	bool isPosK = xd < 0 && yd < 0 || xd > 0 && yd > 0;
	int d = gcd(xd, yd);
	if (d != abs(xd)) {
		cout << "y=" << (isPosK ? "" : "-") << "(" << abs(yd) / d << "/" << abs(xd) / d << ")x";
	} else {
		cout << "y=" << (isPosK ? "" : "-") << abs(yd / d) << "x";
	}

	int xdq = xd * point1[1] - yd * point1[0];
	if (xdq == 0) {
		return;
	}
	bool isPosQ = xd < 0 && xdq < 0 || xd > 0 && xdq > 0;
	d = gcd(xdq, xd);
	if (d != abs(xd)) {
		cout << (isPosQ ? "+" : "-") << "(" << abs(xdq) / d << "/" << abs(xd) / d << ")";
	} else {
		cout << (isPosQ ? "+" : "-") << abs(xdq) / d;
	}
}

void test() {
	char* input1 = new char[MAX_LEN];
	char* input2 = new char[MAX_LEN];
	char* expected = new char[MAX_LEN];
	strcpy_s(input1, MAX_LEN, "(3,6)");
	strcpy_s(input1, MAX_LEN, "(2,4)");
	strcpy_s(expected, MAX_LEN, "y=2x");
	//char *result = func(input1, input2);
	//if (result[0] == expected[0] && result[1] == expected[1]) {
	//	cout << "pass" << endl;
	//} else {
	//	cout << "error : " << result[0] << " " << result[1] << " expected : " << expected[0] << " " << expected[1] << endl;
	//}
}

void homework() {
	char *input1 = new char[MAX_LEN];
	char *input2 = new char[MAX_LEN];
	cin.getline(input1, MAX_LEN, '\n');
	cin.getline(input2, MAX_LEN, '\n');
	func(input1, input2);
}

int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}