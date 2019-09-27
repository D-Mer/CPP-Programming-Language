#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <ctime>


using namespace std;

void printMap(map<char, int> items) {
	map<int, char> valueMap;
	for (map<char, int>::iterator i = items.begin(); i != items.end(); i++) {
		valueMap[i->second] = i->first;
	}
	cout << "[";
	for (map<int, char>::iterator i = --valueMap.end(); i != valueMap.begin(); i--) {
		cout << i->first << ",";
	}
	cout << (valueMap.begin())->first << "]";
}

//���������Ч�ʷǳ��ͣ��ӽ�10s��������û�и���Ķ�д��ʽ
void characterCount(string filename) {
	map<char, int> result;
	ifstream mycout(filename, ios::in);
	string input;
	char c;
	try {
		while (mycout.get(c)) {
			if (isascii(c) && isalpha(c)) {
				c = tolower(c);
				result[c] += 1;
			}
		}
		printMap(result);
	} catch (const exception& e) {
		cerr << e.what() << endl;
	}
}

const int MAXN = 10000000;
const int MAXS = 60 * 1024 * 1024;

//void characterCount2(string filename) {
//	map<char, int> result;
//	int numbers[MAXN];
//	char buf[MAXS];
//	int fd = open(filename, O_RDONLY);
//	int len = read(fd, buf, MAXS);
//	buf[len] = '\0';
//	char c;
//	try {
//		for (size_t i = 0; i < len; i++) {
//			if (isascii(c) && isalpha(c)) {
//				c = tolower(c);
//				result[c] += 1;
//			}
//		}
//		printMap(result);
//
//	} catch (const exception& e) {
//			cerr << e.what() << endl;
//		}
//}

void test() {
	string filename = "E:\\��ǰ�γ�\\c++�߼��������\\MyProgram\\test.txt";//E:\\��ǰ�γ�\\c++�߼��������\\MyProgram\\test.txt
	characterCount(filename);
}

void homework() {
	//int start = clock();
	string filename = "E:\\��ǰ�γ�\\c++�߼��������\\MyProgram\\Q9\\��Ŀ\\Q30\\input.txt";
	characterCount(filename);
	//printf("%.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);
	//start = clock();
	//characterCount2(filename);
	//printf("%.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);
}


int main() {
	//test();
	homework();
	//system("pause");
}