#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <typeinfo>
#include <cmath>

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

enum Triangle {
	ORT, /* Ordinary Right */
	LRT, /* Isosceles Right */
	OIT, /* Ordinary Isosceles */
	ET, /* Equilateral */
	OT, /* Ordinary */
	NT /* not a triangle */
};

map<Triangle, string> Descriptions = {
	{ORT, "ORT"}, {LRT, "LRT"}, {OIT, "OIT"}, {ET, "ET"}, {OT, "OT"}, {NT, "NT"}
};

bool isTriangle(pair<long double, long double> p1, pair<long double, long double> p2, pair<long double, long double> p3) {
	pair<long double, long double> v1 = make_pair(p1.first - p2.first, p1.second - p2.second);
	pair<long double, long double> v2 = make_pair(p1.first - p3.first, p1.second - p3.second);
	if ((v1.first == 0 && v1.second == 0) || (v2.first == 0 && v2.second == 0)) {
		return false;
	} else if ((v1.first == 0 && v2.first == 0) || (v1.second == 0 && v2.second == 0)) {
		return false;
	} else if (v1.first / v2.first == v1.second / v2.second) {
		return false;
	}
	return true;
}

Triangle classify(long double edge1, long double edge2, long double edge3) {
	Triangle result;
	if (((edge1 + edge2) == edge3) || ((edge1 + edge3) == edge2) || ((edge3 + edge2) == edge1)) {
		if (edge1 == edge2 || edge2 == edge3 || edge1 == edge3) {
			result = LRT;
		} else {
			result = ORT;
		}
	} else if (edge1 == edge2 || edge2 == edge3 || edge1 == edge3) {
		if (edge1 == edge2 && edge2 == edge3 && edge1 == edge3) {
			result = ET;
		} else {
			result = OIT;
		}
	} else {
		result = OT;
	}
	return result;
}

string triangleClassify(string input) {
	Triangle result;
	vector<string> points = split(input.substr(1, input.length() - 2), ",");
	pair<long double, long double> p1 = make_pair(stoll(points[0]), stoll(points[1]));
	pair<long double, long double> p2 = make_pair(stoll(points[2]), stoll(points[3]));
	pair<long double, long double> p3 = make_pair(stoll(points[4]), stoll(points[5]));
	long double edge1 = pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2);
	long double edge2 = pow(p3.first - p2.first, 2) + pow(p3.second - p2.second, 2);
	long double edge3 = pow(p3.first - p1.first, 2) + pow(p3.second - p1.second, 2);
	if (!isTriangle(p1, p2, p3)) {
		result = NT;
	} else {
		result = classify(edge1, edge2, edge3);
	}
	return Descriptions[result];
}

void homework() {
	string raw;
	getline(cin, raw);
	string result = triangleClassify(raw);
	cout << result;
}

void test() {
	string raw = "[0,0,0,3,3,0]";
	string result = triangleClassify(raw);
	if (result != "LRT") {
		cout << "error : " << result << " expected :  LRT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[0,0,2,3,4,0]";
	result = triangleClassify(raw);
	if (result != "OIT") {
		cout << "error : " << result << " expected :  OIT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[0,0,3,1,4,0]";
	result = triangleClassify(raw);
	if (result != "OT") {
		cout << "error : " << result << " expected :  OT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[0,0,3,0,4,0]";
	result = triangleClassify(raw);
	if (result != "NT") {
		cout << "error : " << result << " expected :  NT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[-2147483646, 0, 0, 2147483646, 2147483646, 0]";
	result = triangleClassify(raw);
	if (result != "LRT") {
		cout << "error : " << result << " expected :  LRT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[-2147483646,-2147483646,0,2147483646,2147483646,-2147483646]";
	result = triangleClassify(raw);
	if (result != "OIT") {
		cout << "error : " << result << " expected :  OIT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[-10,-50,8,3,3,0]";
	result = triangleClassify(raw);
	if (result != "OT") {
		cout << "error : " << result << " expected :  OT" << endl;
	} else {
		cout << "pass" << endl;
	}
	raw = "[-10,-50,8,3,30,100]";
	result = triangleClassify(raw);
	if (result != "OT") {
		cout << "error : " << result << " expected :  OT" << endl;
	} else {
		cout << "pass" << endl;
	}
	cout << "done" << endl;
}

int main() {
	test();
	//homework();
	system("pause");
}