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

class CompletedHumburger {
public:
	virtual int getPrice() = 0;
};

class Meat {
public:
	static enum Type {
		beef = 1,
		pork = 2,
		chicken = 3
	};
	virtual int getPrice() = 0;
};

class Beef :public Meat {
private:
	int price = 10;
public:
	int getPrice() {
		return price;
	}
};

class Pork :public Meat {
private:
	int price = 8;
public:
	int getPrice() {
		return price;
	}
};

class Chicken :public Meat {
private:
	int price = 7;
public:
	int getPrice() {
		return price;
	}
};

class Vegetable {
public:
	static enum Type {
		lettuce = 1,
		tomato = 2
	};
	virtual int getPrice() = 0;
};

class Lettuce :public Vegetable {
private:
	int price = 4;
public:
	int getPrice() {
		return price;
	}
};

class Tomato :public Vegetable {
private:
	int price = 3;
public:
	int getPrice() {
		return price;
	}
};

class RawHamburger : public CompletedHumburger {
public:
	int getPrice() {
		return 0;
	}
};


class HamburgerDecorator : public CompletedHumburger {
protected:
	pair<Vegetable*, int> vegs;
	CompletedHumburger* hamburger;

public:
	HamburgerDecorator(CompletedHumburger* hamburger) {
		this->hamburger = hamburger;
	}
	virtual int getPrice() {
		return hamburger->getPrice();
	}
};

class HamburgerWithMeat : public HamburgerDecorator {
private:
	pair<Meat*, int> meats;

public:
	HamburgerWithMeat(CompletedHumburger* hamburger, Meat* meat, int num) : HamburgerDecorator(hamburger), meats(make_pair(meat, num)) {}
	int getPrice() {
		return hamburger->getPrice() + meats.first->getPrice() * meats.second;
	}
};

class HamburgerWithVegetable :public HamburgerDecorator {
private:
	pair<Vegetable*, int> vegs;

public:
	HamburgerWithVegetable(CompletedHumburger* hamburger, Vegetable* veg, int num) : HamburgerDecorator(hamburger), vegs(make_pair(veg, num)) {}
	int getPrice() {
		return hamburger->getPrice() + vegs.first->getPrice() * vegs.second;
	}
};




int main() {
	int m_t, m_num, v_t, v_num;
	cin >> m_t >> m_num >> v_t >> v_num;
	Meat::Type m_type = Meat::Type(m_t);
	Vegetable::Type v_type = Vegetable::Type(v_t);
	Meat* meat = NULL;
	switch (m_type) {
	case Meat::beef:
		meat = new Beef;
		break;
	case Meat::pork:
		meat = new Pork;
		break;
	case Meat::chicken:
		meat = new Chicken;
		break;
	default:
		break;
	}
	Vegetable* veg = NULL;
	switch (v_type) {
	case Vegetable::lettuce:
		veg = new Lettuce;
		break;
	case Vegetable::tomato:
		veg = new Tomato;
		break;
	default:
		break;
	}
	CompletedHumburger* ham = new RawHamburger();
	ham = new HamburgerWithMeat(ham, meat, m_num);
	ham = new HamburgerWithVegetable(ham, veg, v_num);
	cout << ham->getPrice();
	//system("pause");
}