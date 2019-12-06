#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <Windows.h>

using namespace std;

vector<string> split(string input, string seperator) {
	string loop = input + seperator;
	int p;
	vector<string> items;
	while ((p = loop.find(seperator)) != -1) {
		items.push_back(loop.substr(0, p));
		loop = loop.substr(p + seperator.length());
	}
	return items;
}

void func() {

}

bool isPalindra(const string word) {
	int front = 0;
	int tail = word.length() - 1;
	while (tail - front >= 0) {
		if (word.at(front) == word.at(tail)) {
			front++;
			tail--;
			continue;
		} else {
			return false;
		}
	}
	return true;
}

string makeLine(vector<string> words, int maxWidth) {
	string result = "";
	if (words.size() == 1) {
		result = words[0];
		for (size_t i = result.length(); i < maxWidth; i++) {
			result += " ";
		}
		return result;
	}
	int totalLen = 0;
	for (size_t i = 0; i < words.size(); i++) {
		totalLen += words[i].length();
	}
	int blanks = maxWidth - totalLen;
	int base = blanks / (words.size() - 1);
	int r = blanks % (words.size() - 1);
	for (size_t i = 0; i < words.size() - 1; i++) {
		result += words[i];
		for (int i = 0; i < base; i++) {
			result += " ";
		}
		if (r > 0) {
			result += " ";
			r--;
		}
	}
	result += words[words.size() - 1];
	return result;
}

vector<pair<int, int>> findPlaces(vector<string> lines, string word) {
	vector<pair<int, int>> result;
	pair<int, int>* tempPlace;
	string s;
	int p;
	int base = 0;
	for (size_t i = 0; i < lines.size(); i++) {
		s = lines[i];
		while ((p = s.find(word)) != -1) {
			s = s.substr(p + word.length());
			tempPlace = new pair<int, int>;
			tempPlace->first = i + 1;
			tempPlace->second = base + p + 1;
			base += p + word.length();
			result.push_back(*tempPlace);
		}
		base = 0;
	}
	return result;
}

void homework() {
	vector<string> words;
	vector<string> filteredWords;
	vector<string> lines;
	string input;
	int maxWidth;
	int n;
	vector<string> needToFinds;
	getline(cin, input);
	words = split(input.substr(2, input.length() - 4), "\",\"");
	cin >> maxWidth;
	cin >> n;
	for (size_t i = 0; i < words.size(); i++) {
		if (isPalindra(words[i])) {
			continue;
		}
		filteredWords.push_back(words[i]);
	}
	getchar();
	for (int i = 0; i < n; i++) {
		getline(cin, input);
		needToFinds.push_back(input);
	}

	int currentLen = 0;
	string tempLine = "";
	vector<string> tempWords;
	// 合成文本
	for (int i = 0; i < filteredWords.size(); i++) {
		if (currentLen + filteredWords[i].length() <= maxWidth) {
			tempWords.push_back(filteredWords[i]);
			currentLen += filteredWords[i].length() + 1;
		} else {
			// 合成
			tempLine = makeLine(tempWords, maxWidth);

			lines.push_back(tempLine);
			currentLen = 0;
			tempLine.clear();
			tempWords.clear();
			i--;//保留当前词，因为i会递增
		}
	}
	if (tempWords.size() > 0) {
		tempLine = tempWords[0];
		for (size_t i = 1; i < tempWords.size(); i++) {
			tempLine += " " + tempWords[i];
		}
		for (int i = tempLine.length(); i < maxWidth; i++) {
			tempLine += " ";
		}
		lines.push_back(tempLine);
	}

	//寻找出现的位置
	vector<vector<pair<int, int>>> places;
	vector<pair<int, int>> tempPlaces;
	for (size_t i = 0; i < n; i++) {
		tempPlaces = findPlaces(lines, needToFinds[i]);
		places.push_back(tempPlaces);
		tempPlaces.clear();
	}

	//输出字符串
	for (size_t i = 0; i < lines.size(); i++) {
		cout << "\"" << lines[i] << "\"" << endl;
	}

	//输出查找结果
	for (size_t i = 0; i < places.size(); i++) {
		tempPlaces = places[i];
		cout << "(" << tempPlaces[0].first << "," << tempPlaces[0].second << ")";
		for (size_t j = 1; j < tempPlaces.size(); j++) {
			cout << ",(" << tempPlaces[j].first << "," << tempPlaces[j].second << ")";
		}
		if (i != places.size() - 1) {
			cout << endl;
		}
	}

}

void test() {

}

int main() {
	homework();
	//Sleep(1000);
	//system("pause");
}