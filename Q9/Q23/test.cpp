//#include <iostream>
//#include <string>
//#include <vector>
//
//
////#define foreach(i, set) \
////		for (decltype(set.begin()) i = set.begin();it != set.end(); i++)
//using namespace std;
//
//bool isIncrease(string chars) {
//	int len = chars.length();
//	if (len == 1) {
//		return true;
//	}
//	char before = chars.at(0);
//	char c;
//	for (int i = 1; i < len; i++) {
//		c = chars.at(i);
//		if (c < before) {
//			return i;
//		}
//		before = c;
//	}
//	return true;
//}
//
//int getDropPos(string chars) {
//	int len = chars.length();
//	if (len == 1) {
//		return -1;
//	}
//	char before = chars.at(0);
//	char c;
//	for (int i = 1; i < len; i++) {
//		c = chars.at(i);
//		if (c < before) {
//			return i;
//		}
//		before = c;
//	}
//	return -1;
//}
//
//void cut0(string &chars) {
//	for (int i = 0; i < chars.length() - 1; i++) {
//		if (chars.at(i) == '0') {
//			chars = chars.substr(1);
//		}
//		else {
//			break;
//		}
//	}
//}
//
//int checkBefore(int p, string chars) {
//	if (p == 0 || p == 1) {
//		return p + 1;
//	}
//	while (chars.at(p - 2) == chars.at(p - 1)) {
//		p--;
//		if (p == 0 || p == 1) {
//			return p + 1;
//		}
//	}
//	return p;
//}
//
//string increaseDig(string chars) {
//	//string chars;
//	//cin >> chars;
//	int p = getDropPos(chars);
//	cut0(chars);
//	if (p == -1) {
//		cout << chars;
//		return chars;
//	}
//	char low = chars.at(p - 1) - 1;
//	p = checkBefore(p, chars);
//	string result = chars.substr(0, p - 1) + low;
//	int len = chars.length();
//	for (int i = p; i < len; i++)
//	{
//		result += "9";
//	}
//	cut0(result);
//	return result;
//	//cout << result;
//}