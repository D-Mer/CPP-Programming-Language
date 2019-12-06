#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <algorithm>
//#include <windows.h> //这里面有声明Polygon，不能用
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

struct RGB {
	int r;
	int g;
	int b;
};

class Polygon {
protected:
	int id;
	RGB rgb;

public:
	Polygon(int id) : id(id), rgb({ rgb.r = 0,rgb.g = 0, rgb.b = 0 }) {}
	RGB getRGB() {
		return rgb;
	}

	int getId() {
		return id;
	}

	virtual void setRGB(int r, int g, int b) {
		rgb.r = r;
		rgb.g = g;
		rgb.b = b;
	}

	double getGray() {
		return rgb.r * 0.299 + rgb.g * 0.587 + rgb.b * 0.114;
	}

	void print() {
		cout << "P" << id << " " << rgb.r << " " << rgb.g << " " << rgb.b << endl;
	}

	bool operator<(Polygon* p) {
		if (this->getGray() < p->getGray()) {
			return true;
		} else if (this->getGray() == p->getGray()) {
			return this->getId() < p->getId();
		}
		return false;
	}
};

class RedPolygon : public Polygon {
public:
	RedPolygon(int id) : Polygon(id) {}

	void setRGB(int r, int g, int b) {
		rgb.r = r;
	}
};

class ReversePolygon : public Polygon {
public:
	ReversePolygon(int id) : Polygon(id) {}

	void setRGB(int r, int g, int b) {
		rgb.r = 255 - r;
		rgb.g = 255 - g;
		rgb.b = 255 - b;
	}
};

class Board {
private:
	map<int, Polygon*> polygons;
	map<int, vector<Polygon*>> groups;

public:
	void addPolygon(string id, string type) {
		Polygon* polygon = NULL;
		int i = stoi(id.substr(1));
		if (type == "normal") {
			polygon = new Polygon(i);
		} else if (type == "single") {
			polygon = new RedPolygon(i);
		} else if (type == "reverse") {
			polygon = new ReversePolygon(i);
		} else {
			cout << "no such type" << endl;
			return;
		}
		polygons[i] = polygon;
	}

	void addGroup(vector<string> input) {
		int id = stoi(input.back().substr(1));
		int n = stoi(input[1]);
		for (int i = 0; i < n; i++) {
			groups[id].push_back(polygons[stoi(input[2 + i].substr(1))]);
		}
	}

	void set(string id_raw, int r, int g, int b) {
		int id = stoi(id_raw.substr(1));
		char command = id_raw[0];
		if (command == 'P') {
			polygons[id]->setRGB(r, g, b);
		} else if (command == 'G') {
			for (vector<Polygon*>::iterator itr = groups[id].begin(); itr != groups[id].end(); itr++) {
				(*itr)->setRGB(r, g, b);
			}
		} else {
			cout << "no such set command" << endl;
		}
	}

	void print(string command) {
		if (command == "Normal") {
			for (map<int, Polygon*>::iterator itr = polygons.begin(); itr != polygons.end(); itr++) {
				itr->second->print();
			}
		} else if (command == "Gray") {
			vector<Polygon*> grayList;
			map<int, Polygon*>::iterator itr = polygons.begin();
			Polygon* min = itr->second;
			grayList.push_back(min);
			itr++;
			for (; itr != polygons.end(); itr++) {
				size_t i = 0;
				for (; i < grayList.size(); i++) {
					if (*(itr->second) < grayList[i]) {//这里前面的星号注意了，因为重载的是对象，不是指针
						grayList.insert(grayList.begin() + i, itr->second);
						break;
					}
				}
				if (i == grayList.size()) {
					grayList.push_back(itr->second);
				}
			}
			for (vector<Polygon*>::iterator i = grayList.begin(); i != grayList.end(); i++) {
				(*i)->print();
			}
		} else {
			cout << "no such print command" << endl;
		}
	}
};

int main() {
	int n;
	string input;
	vector<string> params;
	Board board;
	cin >> n;
	getchar();
	for (int i = 0; i < n; i++) {
		getline(cin, input);
		params = split(input, " ");
		if (params[0] == "Add") {
			board.addPolygon(params[2], params[1]);
		} else if (params[0] == "Set") {
			board.set(params[1], stoi(params[2]), stoi(params[3]), stoi(params[4]));
		} else if (params[0] == "Group") {
			board.addGroup(params);
		}
	}
	getline(cin, input);
	board.print(input);
	return 0;
}