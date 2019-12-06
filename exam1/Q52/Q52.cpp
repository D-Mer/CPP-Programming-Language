#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <windows.h>
#include <iterator>//这是output.cpp里引用的，可以做输入输出的流迭代器
#include <limits>//这是variable.cpp里引用的，获取一些变量类型的属性

# define max(a, b) (a) > (b) ? (a) : (b)
# define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

extern void input_learn_2();
extern void input_learn();
extern void output2();
extern void wchar_t_learn();
extern void limits_learn();
extern void enum_learn();
extern void enum_learn2();
extern void enum_learn3();
extern void size_learn();
#define random(range) (rand()%(range))
//srand((unsigned)time(NULL));这要写在main函数里
extern void write_learn();
extern void read_learn();

vector<string> split(const string input, const string seperator) {
	string loop = input + seperator;
	vector<string> items;
	int p;
	while ((p = loop.find(seperator)) != -1) {
		items.push_back(loop.substr(0, p));
		loop = loop.substr(p + seperator.length());
	}
	return items;
}

typedef struct Record {
	int year;
	int month;
	int water;
	string city;
	vector<int> rains;
}Record;

typedef struct Query {
	int type;
	int year;
	int month;
	int start_y;
	int start_m;
	int end_y;
	int end_m;
	string city;
}Query;

int cal(const vector<int> rains) {
	int result = 0;
	int left = 0;
	int right = 0;
	for (size_t i = 1; i < rains.size() - 1; i++) {
		left = rains[i];
		right = rains[i];
		//找左边最高值
		for (size_t j = 0; j < i; j++) {
			if (rains[j] > left) {
				left = rains[j];
			}
		}
		//找右边最高值
		for (size_t j = i + 1; j < rains.size(); j++) {
			if (rains[j] > right) {
				right = rains[j];
			}
		}
		//计算
		if (rains[i] < left && rains[i] < right) {
			int m = min(left, right);
			result += m - rains[i];
		}
	}
	return result;
}

void homework() {
	int N;
	int Q;
	cin >> N >> Q;
	getchar();
	string input;
	string time;
	string city;
	vector<string> temp;
	vector<Record> records;
	Record r;
	vector<string> timeRaw;
	vector<int> rains;
	//获取输入
	for (int i = 0; i < N; i++) {
		getline(cin, input);
		temp = split(input.substr(1, input.length() - 2), ",");
		time = temp[0].substr(6, temp[0].length() - 7);
		timeRaw = split(time, "-");
		r.year = stoi(timeRaw[0]);
		r.month = stoi(timeRaw[1]);
		r.city = temp[1].substr(6, temp[1].length() - 7);
		temp.clear();
		getline(cin, input);
		temp = split(input.substr(1, input.length() - 2), ",");
		for (size_t i = 0; i < temp.size(); i++) {
			rains.push_back(stoi(temp[i]));
		}
		r.rains = rains;
		r.water = cal(r.rains);
		records.push_back(r);
		rains.clear();
		temp.clear();
	}
	int type;
	vector<Query> querys;
	Query *q;
	//获取查询指令
	for (int i = 0; i < Q; i++) {
		cin >> type; getchar();
		getline(cin, input);
		q = new Query();
		switch (type) {
		case 1:
			q->type = 1;
			temp = split(input.substr(1, input.length() - 2), ",");
			time = temp[0].substr(6, temp[0].length() - 7);
			timeRaw = split(time, "-");
			q->year = stoi(timeRaw[0]);
			q->month = stoi(timeRaw[1]);
			q->city = temp[1].substr(6, temp[1].length() - 7);
			querys.push_back(*q);
			break;
		case 2:
			q->type = 2;
			input = input.substr(7, input.length() - 9);
			q->city = input;
			querys.push_back(*q);
			break;
		case 3:
			q->type = 3;
			temp = split(input.substr(1, input.length() - 2), ",");
			time = temp[0].substr(7, temp[0].length() - 8);
			timeRaw = split(time, "-");
			q->start_y = stoi(timeRaw[0]);
			q->start_m = stoi(timeRaw[1]);
			time = temp[1].substr(5, temp[1].length() - 6);
			timeRaw = split(time, "-");
			q->end_y = stoi(timeRaw[0]);
			q->end_m = stoi(timeRaw[1]);
			querys.push_back(*q);
			break;
		case 4:
			q->type = 4;
			temp = split(input.substr(1, input.length() - 2), ",");
			city = temp[0].substr(6, temp[0].length() - 7);
			time = temp[1].substr(7, temp[1].length() - 8);
			timeRaw = split(time, "-");
			q->city = city;
			q->start_y = stoi(timeRaw[0]);
			q->start_m = stoi(timeRaw[1]);
			time = temp[2].substr(5, temp[2].length() - 6);
			timeRaw = split(time, "-");
			q->end_y = stoi(timeRaw[0]);
			q->end_m = stoi(timeRaw[1]);
			querys.push_back(*q);
			break;
		default:
			break;
		}
	}

	//执行指令
	for (size_t i = 0; i < querys.size(); i++) {
		q = &querys[i];
		bool found = false;
		int result=0;
		bool timeFlag = false;
		bool cityFlag = false;
		switch (q->type) {
		case 1:
			for (size_t j = 0; j < records.size(); j++) {
				r = records[j];
				if (r.city == q->city && r.year == q->year && r.month == q->month) {
					found = true;
					cout << r.water << endl;
				}
			}
			if (!found) {
				cout << "Not Found!" << endl;
			}
			break;
		case 2:
			for (size_t j = 0; j < records.size(); j++) {
				r = records[j];
				if (r.city == q->city) {
					found = true;
					result += r.water;
				}
			}
			if (!found) {
				cout << "Not Found!" << endl;
			}
			else {
				cout << result << endl;
			}
			result = 0;
			break;
		case 3:
			for (size_t j = 0; j < records.size(); j++) {
				r = records[j];
				if (r.year >= q->start_y && r.year<= q->end_y ) {
					if (r.year == q->start_y) {
						if (r.month < q->start_m) {
							continue;
						}
					}
					if (r.year == q->end_y) {
						if (r.month > q->end_m) {
							continue;
						}
					}
					found = true;
					result += r.water;
				}
			}
			if (!found) {
				cout << "Not Found!" << endl;
			}
			else {
				cout << result << endl;
			}
			result = 0;
			break;
		case 4:
			for (size_t i = 0; i < records.size(); i++) {
				r = records[i];
				if (r.city == q->city) {
					cityFlag = true;
					if (r.year >= q->start_y && r.year <= q->end_y) {
						if (r.year == q->start_y) {
							if (r.month < q->start_m) {
								continue;
							}
						}
						if (r.year == q->end_y) {
							if (r.month > q->end_m) {
								continue;
							}
						}
						found = true;
						timeFlag = true;
						result += r.water;
					}
				}
			}
			if (!cityFlag) {
				cout << "Area Not Found!" << endl;
			}
			else if(!timeFlag) {
				cout << "Time Not Found!" << endl;
			}
			else {
				cout << result << endl;
			}
			result = 0;
			break;
		default:
			break;
		}
	}
}

int main() {
	homework();
	//Sleep(1000);
	//system("pause");
}



