#include <iostream>
#include <windows.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

const int MAX_LEN = 900;

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


struct Bomb {
	int x;
	int y;
};


int main() {
	size_t xNum, yNum, bombNum, power;
	cin >> xNum >> yNum >> bombNum >> power;
	char* input = new char[MAX_LEN];
	cin.getline(input, MAX_LEN, '\n');
	cin.getline(input, MAX_LEN, '\n');

	Bomb *bombs = new Bomb[MAX_LEN];
	char* s = new char[MAX_LEN];
	strcpy_s(s, MAX_LEN, input);
	char** rawBombs = splitchars(subchars(s,1, strlen(s-2)), "),(", MAX_LEN);
	for (size_t i = 0; i < bombNum; i++) {
		char* temp = rawBombs[i];
		Bomb b;
		b.x = atoi(splitchars(temp, ",", 10)[0]);
		b.y = atoi(splitchars(temp, ",", 10)[1]);
		bombs[i] = b;
	}
	int** allPoints = new int*[xNum];
	for (size_t i = 0; i < yNum; i++) {
		allPoints[i] = new int[yNum];
	}
	bool flag = false;
	for (int i = 1; i <= xNum; i++) {
		for (int j = 1; j <= yNum; j++) {
			for (int k = 0; k < bombNum; k++) {
				if (i==bombs[k].x && abs(j - bombs[k].y) < power 
					|| j == bombs[k].y && abs(i - bombs[k].x) < power) {
					if (!flag) {
						cout << "(" << i << "," << j << ")";
						flag = true;
					} else {
						cout << ",(" << i << "," << j << ")";
					}
					break;
				}
			}
		}
	}
	cout << endl;
	//system("pause");
	//Sleep(1000);
}

