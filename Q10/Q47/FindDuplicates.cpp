#include <iostream>
#include <windows.h>

using namespace std;

const int MAX_LEN = 100000;

char* subchars(const char* raw, const size_t begin, const size_t end) {
	size_t maxlen = strlen(raw);
	char* buf = new char[maxlen];
	raw += begin;
	size_t i = 0;
	for (i = 0; i < end - begin; i++) {
		buf[i] = raw[i];
	}
	buf[i] = '\0';
	return buf;
}

char** splitchars(const char* raw, const char* seperator, const size_t maxsublen) {
	int p = 0;//���˼��εļ���
	int rawlen = strlen(raw);
	int seplen = strlen(seperator);
	int maxsubnum = rawlen / seplen + 3;
	char** result = new char*[maxsubnum];
	const char* buf = raw;
	for (size_t i = 0; i < maxsubnum; i++) {
		result[i] = new char[maxsublen];
	}
	size_t i = 0;//�ͷָ����Ƚϵļ���
	size_t currentlen = 0;//��ǰ�εĳ���
	while (*buf != '\0' || strlen(buf) > seplen) {
		//ѭ��ƥ�䣬����˳�ʱi==len2��˵��ƥ��ɹ�
		for (i = 0; i < seplen; i++) {
			if (buf[i] != seperator[i]) {
				break;
			}
		}
		if (i == seplen) {
			//���ƽس���һ�β�����
			size_t j = 0;
			for (j = 0; j < currentlen; j++) {
				result[p][j] = raw[j];
			}
			result[p][j] = '\0';

			//��ʼ����������
			buf += seplen;
			raw = buf;
			p++;
			currentlen = 0;
		} else {//�������ǰ��
			buf++;
			currentlen++;
		}
	}
	if (*raw) {
		for (i = 0; i < strlen(raw); i++) {
			result[p][i] = raw[i];
		}
		result[p][i] = '\0';
		result[p + 1] = '\0';
	} else {
		result[p] = '\0';
	}
	return result;
}

// ʹ�ÿ���ָ��ķ�����ǰ����һ��ѭ��ʱ�����ݶ������飬���㷨��û��ʵ�ʹ�ϵ
int func(const char* input) {
	char** rawNums = splitchars(subchars(input, 1, strlen(input) - 1), ",", 100);
	int nums[MAX_LEN];
	int n = 0;
	while (rawNums[n]) {
		nums[n] = atoi(rawNums[n]);
		n++;
	}

	int fast = nums[0];
	int slow = nums[0];
	// Ѱ�һ����
	do {
		fast = nums[nums[fast]];
		slow = nums[slow];
	} while (fast != slow);

	fast = nums[0];
	while (fast != slow) {
		fast = nums[fast];
		slow = nums[slow];
	}
	return fast;
}

void test() {
	const char* input = new char[MAX_LEN];
	int expected = 2;
	input = "[1,3,4,2,2]";
	int result = func(input);
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
	input = "[2,3,4,1,2]";
	expected = 2;
	result = func(input);
	if (result == expected) {
		cout << "pass" << endl;
	} else {
		cout << "error : " << result << " expected : " << expected << endl;
	}
}

void homework() {
	char *input = new char[MAX_LEN];
	cin.getline(input, MAX_LEN, '\n');
	int result = func(input);
	cout << result;
}

int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}