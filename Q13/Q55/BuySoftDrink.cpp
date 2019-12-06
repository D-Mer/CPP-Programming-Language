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


using namespace std;

class MyExcepion {
private:
	int code;
	string msg;
public:
	MyExcepion() {
		this->code = 0;
		this->msg = "";
	}

	explicit MyExcepion(int code) {
		this->code = code;
		this->msg = "";
	}

	explicit MyExcepion(string msg) {
		this->code = 0;
		this->msg = msg;
	}

	MyExcepion(int code, string msg) {
		this->code = code;
		this->msg = msg;
	}

	int getCode() {
		return code;
	}

	string getMessage() {
		return msg;
	}
};

class DrinkOverflowException : public MyExcepion {
public:
	explicit DrinkOverflowException(string msg) : MyExcepion(msg) {};
};

class DrinkNotFoundException : public MyExcepion {
public:
	explicit DrinkNotFoundException(string msg) : MyExcepion(msg) {};
};


class Drink {
private:
	string name;
public:
	enum Type {
		coffee = 1,
		milk = 2,
		tea = 3,
		beer = 4
	};

	void setName(string name) {
		this->name = name;
	};

	string getName() {
		return this->name;
	}

	virtual void buy() {
		cout << "super buy" << endl;
	};
	virtual ~Drink() = default;
};

class Coffee : public Drink {
private:
	const static int price = 5;
public:
	explicit Coffee(string name) {
		this->setName(name);
	}

	void buy() override {
		cout << getName() << ":" << price << endl;
	}

	~Coffee() override = default;
};

class Milk : public Drink {
private:
	const static int price = 4;
public:
	explicit Milk(string name) {
		this->setName(name);
	}

	void buy() override {
		cout << getName() << ":" << price << endl;
	}

	~Milk() override = default;
};

class Tea : public Drink {
private:
	const static int price = 3;
public:
	explicit Tea(string name) {
		this->setName(name);
	}

	void buy() override {
		cout << getName() << ":" << price << endl;
	}

	~Tea() override = default;
};

class Beer : public Drink {
private:
	const static int price = 6;
public:
	explicit Beer(string name) {
		this->setName(name);
	}

	void buy() override {
		cout << getName() << ":" << price << endl;
	}

	~Beer() override = default;
};

class DrinkFactory {
public:
	static Drink* getDrink(Drink::Type type) {
		Drink *drink = NULL;
		switch (type) {
		case Drink::coffee:
			drink = new Coffee("coffee");
			break;
		case Drink::milk:
			drink = new Milk("milk");
			break;
		case Drink::tea:
			drink = new Tea("tea");
			break;
		case Drink::beer:
			drink = new Beer("beer");
			break;
		default:
			break;
		}
		return drink;
	};
};

class Hub {
private:
	int stock{};
	map<Drink::Type, vector<Drink*>> drink_stock;//这里Drink要用指针，不然会把子类对象强转为父类。。。丢失子类的属性和方法。坑了好久
	static const int MAX_STOCK = 10;
	static Hub *Hub_Instance;
public:
	static Hub *getInstance() {
		if (Hub_Instance == nullptr) {
			Hub_Instance = new Hub();
			Hub_Instance->stock = 0;
		}
		return Hub_Instance;
	}

	void add(Drink::Type type, int num) throw(DrinkOverflowException) {
		if (stock + num > MAX_STOCK) {
			throw DrinkOverflowException("DrinkOverflow");
		}
		for (int i = 0; i < num; i++) {
			drink_stock[type].push_back(DrinkFactory::getDrink(type));
			stock++;
		}
	}

	void buy(Drink::Type type) throw(DrinkNotFoundException) {
		Drink* drink;
		if (drink_stock[type].empty()) {
			drink = DrinkFactory::getDrink(type);
			string temp = drink->getName() + " is not found";
			throw DrinkNotFoundException(temp);
		}
		drink = drink_stock[type].back();
		drink->buy();
		drink_stock[type].pop_back();
		delete drink;
		stock--;
	}
};
Hub* Hub::Hub_Instance = NULL;

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
	int command;
	Drink::Type type;
	int num;
	bool end = false;
	Hub *hub = Hub::getInstance();
	while (!end) {
		cin >> command;
		int temp;
		switch (command) {
		case 1:
			cin >> temp;
			type = Drink::Type(temp);
			cin >> num;
			try {
				hub->add(type, num);
			} catch (DrinkOverflowException& e) {
				cout << e.getMessage() << endl;
			}
			break;
		case 2:
			cin >> temp;
			type = Drink::Type(temp);
			try {
				hub->buy(type);
			} catch (DrinkNotFoundException& e) {
				cout << e.getMessage() << endl;
			}
			break;
		case 3:
			end = true;
			break;
		default:
			break;
		}
	}
	//Sleep(1000);
	//system("pause");
}