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

class MyExcepion {
private:
	int code;
	string msg;
public:
	MyExcepion() : code(0), msg("") {}
	MyExcepion(int code) : code(code), msg("") {}
	MyExcepion(string msg) : code(0), msg(msg){}
	MyExcepion(int code, string msg) : code(code), msg(msg) {}
	int getCode() {
		return code;
	}
	string getMessage() {
		return msg;
	}
};

class NothingLeftException : public MyExcepion {
public:
	NothingLeftException() : MyExcepion("Nothing Left") {}
};

class NoSuchGoodsException : public MyExcepion {
public:
	NoSuchGoodsException() : MyExcepion("No Such Commodity") {}
};

class OverFlowException : public MyExcepion {
public:
	OverFlowException() : MyExcepion("Overflow") {}
};

class UnenoughMoneyException : public MyExcepion {
public:
	UnenoughMoneyException() : MyExcepion("Can not Afford") {}
};

class Commodity {
private:
	int id;
	double price;

public:
	Commodity(int id) : id(id) {
		switch (id) {
		case 1:
			price = 10;
			break;
		case 2:
			price = 15;
			break;
		case 3:
			price = 20;
			break;
		default:
			cout << "error type : " << id << endl;
		}
	}

	double getPrice() {
		return price;
	}
	friend class Bourse;
};

class Bourse {
private:
	double money;
	int MAX;
	map<int, vector<Commodity>> storage;
	int Size() {
		int r = 0;
		for (auto itr = storage.begin(); itr != storage.end(); itr++) {
			r += itr->second.size();
		}
		return r;
	}

public:
	Bourse(int max, double money) : MAX(max), money(money){}

	void add(Commodity c) throw (MyExcepion&) {
		if (Size() == MAX) {
			throw OverFlowException();
		}
		if (money < c.price) {
			throw UnenoughMoneyException();
		}
		money -= c.price;
		storage[c.id].push_back(c);
		cout << money << endl;
	}

	void sell(int id, int amount) throw (MyExcepion&) {
		if (Size() == 0) {
			throw NothingLeftException();
		}
		if (storage[id].size() < amount) {
			throw NoSuchGoodsException();
		}
		Commodity& c = storage[id].back();
		money += c.price * 1.2;
		storage[id].pop_back();
		cout << money << endl;
	}

};



int main() {
	int max;
	double money;
	int code, id;
	
	cin >> max >> money;

	Bourse bourse(max, money);

	while (true) {
		cin >> code;
		try {
			if (code == -1) {
				break;
			} else if (code == 0) {
				cin >> id;
				bourse.sell(id, 1);
			} else if (code == 1) {
				cin >> id;
				bourse.add(id);
			} else {
				cout << "no such operation code : " << code << endl;
			}
		} catch (MyExcepion& e) {
			cout << e.getMessage() << endl;
		}
	}

	return 0;
}