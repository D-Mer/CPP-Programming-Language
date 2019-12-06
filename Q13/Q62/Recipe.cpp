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

class Food {
private:
	double car;
	double pro;
	double DF;
	double fat;

protected:
	Food(double car, double pro, double DF, double fat) {
		this->car = car;
		this->pro = pro;
		this->DF = DF;
		this->fat = fat;
	}

public:
	double getCar() {
		return this->car;
	}
	double getPro() {
		return this->pro;
	}
	double getDF() {
		return this->DF;
	}
	double getFat() {
		return this->fat;
	}
};

class Rice : public Food {
public:
	Rice() : Food(16.2, 3.7, 0, 0) {}
};

class Beef : public Food {
public:
	Beef() : Food(1.8, 17.5, 0, 7.2) {}
};

class Bro : public Food {
public:
	Bro() : Food(0.2, 0.4, 3.6, 0) {}
};

class Oat : public Food {
public:
	Oat() : Food(12.3, 5.7, 7.3, 3) {}
};

class Duck : public Food {
public:
	Duck() : Food(6.9, 9, 0, 9.3) {}
};

class Cab : public Food {
public:
	Cab() : Food(2.1, 0.8, 4.3, 0) {}
};


class Diet {
private:
	vector<Food*> foods;
	static const double min_car;
	static const double min_pro;
	static const double min_DF;
	static const double max_fat;

public:
	bool isHealthy() {
		double car = 0;
		double pro = 0;
		double DF = 0;
		double fat = 0;
		Food* food;
		for (size_t i = 0; i < foods.size(); i++) {
			food = foods[i];
			car += food->getCar();
			pro += food->getPro();
			DF += food->getDF();
			fat += food->getFat();
		}
		return car >= min_car && pro >= min_pro && DF >= min_DF && fat <= max_fat;
	}

	Diet& operator+=(Food& food) {
		this->foods.push_back(&food);
		return *this;
	}

};
const double Diet::min_car = 13.3;
const double Diet::min_pro = 13.5;
const double Diet::min_DF = 3.3;
const double Diet::max_fat = 10.3;

int main() {
	Diet diet;
	int x;
	Food* food;
	while (cin >> x) {
		switch (x) {
		case 1:
			food = new Rice();
			diet += *food;
			break;
		case 2:
			food = new Beef();
			diet += *food;
			break;
		case 3:
			food = new Bro();
			diet += *food;
			break;
		case 4:
			food = new Oat();
			diet += *food;
			break;
		case 5:
			food = new Duck();
			diet += *food;
			break;
		case 6:
			food = new Cab();
			diet += *food;
			break;
		default:
			cout << -1;
			return 0;
		}
	}
	if (diet.isHealthy()) {
		cout << "healthy";
	} else {
		cout << "unhealthy";
	}
	//system("pause");
	return 0;
}