#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <windows.h>
#include <iterator>//这是output.cpp里引用的，可以做输入输出的流迭代器
#include <limits>//这是variable.cpp里引用的，获取一些变量类型的属性
#include <locale.h>

# define max(a, b) (a) > (b) ? (a) : (b)
# define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

class Comparable {
public:
	virtual void operator<(const Comparable& c);
	virtual void operator==(const Comparable& c);
};

template<class T>
class MyClass {
private:
	vector<T> contents;
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}

public:
	void push_back(T a) {
		contents.push_back(a);
	}

	void sort() {
		for (size_t i = 0; i < contents.size(); i++) {
			for (size_t j = i + 1; j < contents.size(); j++) {
				if (contents[i] > contents[j]) {
					swap(contents[i], contents[j]);
				}
			}
		}
	}

	int findCmpCount(T t) {
		int left = 0;
		int right = contents.size() - 1;
		int p;
		int count = 0;
		do {
			p = (left + right) / 2;
			count++;
			if (t == contents[p]) {
				return count;
			} else if (t < contents[p]) {
				right = p - 1;
			} else {
				left = p + 1;
			}
		} while (left <= right);
		return count;
	}

};

void getTest() {
	string input;
	ofstream mycout("E:\\当前课程\\c++高级程序设计\\MyProgram\\test.txt", ios::app);
	while (getline(cin, input)) {
		mycout << input << endl;
	}
	cin >> input;
	mycout << "------------------------------" << endl;
	mycout.close();
}

int main() {
	int n, a;
	char c;
	double d;
	cin >> n;
	MyClass<int> ints;
	MyClass<char> chars;
	MyClass<double> doubles;
	for (int i = 0; i < n; i++) {
		cin >> a;
		ints.push_back(a);
	}
	ints.sort();
	cin >> a;
	cout << ints.findCmpCount(a) << endl;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> d;
		doubles.push_back(d);
	}
	doubles.sort();
	cin >> d;
	cout << doubles.findCmpCount(d) << endl;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c;
		chars.push_back(c);
	}
	chars.sort();
	cin >> c;
	cout << chars.findCmpCount(c) << endl;

	//Sleep(1000);
	return 0;
}