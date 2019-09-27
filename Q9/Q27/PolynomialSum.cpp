#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

vector<string> split(string raw, string seperator) {
	string loop = raw + seperator;
	vector<string> items;
	int p;
	while ((p = loop.find(seperator)) != -1) {
		items.push_back(loop.substr(0, p));
		loop = loop.substr(p + seperator.length());
	}
	return items;
}

class Polynomial {
private:
	map<int, int> items;
public:
	Polynomial(string raw) {
		vector<string> mids = split(raw, " + ");
		vector<string> values;
		for (size_t i = 0; i < mids.size(); i++) {
			values = split(mids[i], "x^");
			if (items.find(stoi(values[1])) != items.end()) {
				this->items[stoi(values[1])] += stoi(values[0]);
			} else {
				this->items[stoi(values[1])] = stoi(values[0]);
			}
		}
	}
	~Polynomial() {
	}

	void add(Polynomial p2) {
		for (map<int, int>::iterator i = p2.items.begin(); i != p2.items.end(); i++) {
			if (items.find(i->first) != items.end()) {
				items[i->first] += p2.items[i->first];
			} else {
				items[i->first] = p2.items[i->first];
			}
		}
	}

	string to_string() {
		string result = "";
		for (map<int, int>::iterator i = --items.end(); i != items.begin(); i--) {
			if (i->second == 0) {
				continue;
			} else {
				result += std::to_string(i->second) + "x^" + std::to_string(i->first) + " + ";
			}
		}
		result += std::to_string(items.begin()->second) + "x^" + std::to_string(items.begin()->first);
		return result;
	}
};


string polynomialAdd(string poly1, string poly2) {
	Polynomial p1 = Polynomial(poly1);
	Polynomial p2 = Polynomial(poly2);
	p1.add(p2);
	return p1.to_string();
}


void test() {
	string s1 = "2x^6 + 3x^5 + 12x^3 + 6x^1 + 20x^0";
	string s2 = "2x^6 + 3x^5 + 12x^2 + 6x^1 + 20x^0";
	string expected = "4x^6 + 6x^5 + 12x^3 + 12x^2 + 12x^1 + 40x^0";
	string result = polynomialAdd(s1, s2);
	if (expected == result) {
		cout << "right";
	}
	else {
		cout << "error : " << result << " , expected : " << expected;
	}
}

void homework() {
	string poly1, poly2;
	getline(cin, poly1);
	getline(cin, poly2);
	string result = polynomialAdd(poly1, poly2);
	cout << result;
}

void getTest() {
	string input;
	ofstream mycout("E:\\当前课程\\c++高级程序设计\\MyProgram\\test.txt", ios::app);
	while (getline(cin, input)) {
		mycout << input << endl;

	}
	cin >> input;
	mycout << "done" << endl;
	mycout.close();
}

int main() {
	//getTest();
	//test();
	homework();
	//system("pause");
}