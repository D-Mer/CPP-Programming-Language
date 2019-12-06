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
#include <locale.h>

# define max(a, b) (a) > (b) ? (a) : (b)
# define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

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


class GPU {
private:
	int price;
	int hashrate;

protected:
	GPU(int price, int hashrate) {
		this->price = price;
		this->hashrate = hashrate;
	}

public:
	virtual double calculate() = 0;
	int setPrice(int price) {
		return this->price = price;
	}
	int setHashrate(int hashrate) {
		return this->hashrate = hashrate;
	}
	int getPrice() {
		return this->price;
	}
	int getHashrate() {
		return this->hashrate;
	}
	friend istream& operator>>(istream& in, GPU& gpu);
};

class GPU_1 : public GPU {
private:
	double elect_cost = 16.2;

public:
	GPU_1(int price, int hashrate) : GPU(price, hashrate) {}

	double calculate() {
		return GPU::getHashrate() * 0.02 - this->elect_cost;
	}
};

class GPU_2 : public GPU {
private:
	double elect_cost = 28.8;

public:
	GPU_2(int price, int hashrate) : GPU(price, hashrate) {}

	double calculate() {
		return GPU::getHashrate() * 0.02 - this->elect_cost;
	}
};

class GPU_3 : public GPU {
private:
	double elect_cost = 19.44;

public:
	GPU_3(int price, int hashrate) : GPU(price, hashrate) {}

	double calculate() {
		return GPU::getHashrate() * 0.02 - this->elect_cost;
	}
};

istream& operator>>(istream& in, GPU& gpu) {
	int price;
	int hashrate;
	in >> price >> hashrate;
	gpu.setPrice(price);
	gpu.setHashrate(hashrate);
	return in;
}

int main() {
	//为什么要强行写一个带参构造器？这题好像直接无参构造+cin初始化就行了吧？cin>>必须要有一个对象啊kora！！
	GPU* g1 = new GPU_1(0, 0);
	GPU* g2 = new GPU_2(0, 0);
	GPU* g3 = new GPU_3(0, 0);
	cin >> *g1 >> *g2 >> *g3;

	double income = 0;
	income += g1->calculate() + g2->calculate() + g3->calculate();
	int cost = g1->getPrice() + g2->getPrice() + g3->getPrice();
	if (income <= 0) {
		cout << -1;
	} else {
		double temp = cost / income;
		if (temp == (int)temp) {
			cout << temp;
		}
		else {
			cout << (int)temp + 1;
		}

	}
	//system("pause");
	return 0;
}