#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <iomanip>
#include <windows.h> //这里面有声明Polygon，不能用
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

class Car {
public:
	Car(string id) : id(id) {}
	virtual ~Car() {};
	enum Type {
		Small = 'S',
		Mediun = 'M',
		Large = 'L'
	};

	void wait() {
		this->wait_time--;
	}

	bool redFace() {
		return wait_time == 0;
	}

	void park() {
		this->park_time--;
	}

	bool readyToLeave() {
		return this->park_time == 0;
	}

	void leave() {
		delete this;
	}

	int getSize() {
		return this->size;
	}

	double getFee() {
		return this->fee;
	}

	string getId() {
		return id;
	}

protected:
	string id;
	int size;
	int park_time;
	int wait_time;
	double fee;
};

class SmallCar : public Car {
public:
	SmallCar(string id) : Car(id) {
		this->size = 2;
		this->park_time = 3;
		this->wait_time = 1;
		this->fee = 1.5;
	}
	//~SmallCar() {
	//	delete this;
	//}
};

class MediumCar : public Car {
public:
	MediumCar(string id) : Car(id) {
		this->size = 3;
		this->park_time = 2;
		this->wait_time = 2;
		this->fee = 3;
	}
	~MediumCar() {}
};

class LargeCar : public Car {
public:
	LargeCar(string id) : Car(id) {
		this->size = 4;
		this->park_time = 1;
		this->wait_time = 3;
		this->fee = 4.5;
	}
	~LargeCar() {}
};

class CarFactory {
public:
	static Car* createCar(string id, Car::Type type) {
		Car* car = nullptr;
		switch (type) {
		case Car::Small:
			car = new SmallCar(id);
			break;
		case Car::Mediun:
			car = new MediumCar(id);
			break;
		case Car::Large:
			car = new LargeCar(id);
			break;
		default:
			cout << "no such type car" << endl;
			break;
		}
		return car;
	}
};

class ParkingLot {
public:
	ParkingLot(int n, string weather) : space(vector<Car*>(2 * n, nullptr)), weather(weather) {}
	~ParkingLot() {}

	void doClock() {
		tryPark();
		printCurrentPlaces();
		updateSpace();
		updateCars();
	}

	void CarComes(string type, string id) {
		cars.push_back(CarFactory::createCar(id, Car::Type(type[0])));
	}

	int getSpaceIndex(int size) {
		int count = 0;
		for (size_t i = 0; i < space.size(); i++) {
			if (space[i] == nullptr) {
				count++;
				if (count >= size) {
					return i - size + 1;
				}
			} else {
				i += space[i]->getSize() - 1;
				count = 0;
			}
		}
		return -1;
	}

	void updateSpace() {
		for (size_t i = 0; i < space.size(); i++) {
			if (space[i] != nullptr) {
				space[i]->park();
				if (space[i]->readyToLeave()) {
					profit += space[i]->getFee();
					int s = space[i]->getSize();
					space[i]->leave();
					space[i] = nullptr;
					i += s - 1;
				}

			}
		}
		if (weather == "sunny") {
			adjustSpace();
		}
	}

	void adjustSpace() {
		int current = 0;
		for (size_t i = 0; i < space.size(); i++) {
			if (space[i] != nullptr) {
				if (current != i) {
					space[current] = space[i];
					space[i] = nullptr;
				}
				i += space[current]->getSize() - 1;
				current += space[current]->getSize();
			}
		}
	}

	void tryPark() {
		int idle;
		while (cars.size() != 0) {
			idle = getSpaceIndex(cars[0]->getSize());
			if (idle < 0) {
				return;
			} else {
				space[idle] = cars[0];
				cars.erase(cars.begin());
			}
		}
		
	}

	void updateCars() {
		for (size_t i = 0; i < cars.size(); i++) {
			cars[i]->wait();
			if (cars[i]->redFace()) {
				cars[i]->leave();
				cars.erase(cars.begin() + i);
				i--;
			}
		}
	}

	void printCurrentPlaces() {
		bool found = false;
		for (size_t i = 0; i < space.size(); i++) {
			if (space[i] != nullptr) {
				cout << (found ? " " : "") << space[i]->getId();
				found = true;
				i += space[i]->getSize() - 1;
			}
		}
		if (!found) {
			cout << "null";
		}
		cout << endl;
	}

	bool isEnd() {
		auto itr = space.begin();
		while (itr != space.end()) {
			if ((*itr) != nullptr) {
				return false;
			}
			itr++;
		}
		return cars.empty();
	}

	void printProfit() {
		cout << profit;
	}

private:
	double profit;
	string weather;
	vector<Car*> space;
	vector<Car*> cars;
};

template<class T>
void clearVector(vector<T>& vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		vec[i].~T();
	}
	vec.clear();
}


int main() {
	string input;
	getline(cin, input);
	vector<string> params = split(input, " ");
	ParkingLot lot(stoi(params[0]), params[1]);
	clearVector(params);
	//cout.setf(ios::fixed);//设置浮点数输出格式，需要#include <iomanip>
	//cout << fixed << setprecision(1) << 1.33 << endl;//输出小数点后1位(四舍五入)
	while (true) {
		getline(cin, input);
		params = split(input, " ");
		if (params[0] == "in") {
			lot.CarComes(params[1], params[2]);
			lot.doClock();
		} else if (params[0] == "end") {
			while (!lot.isEnd()) {
				lot.doClock();
			}
			cout << "null" << endl;
			lot.printProfit();
			break;
		}
		clearVector(params);
	}
	clearVector(params);
	//Sleep(1000);
	return 0;
}