#include <iostream>
#include <windows.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

template<class T, size_t N>
size_t getArrayLen(T(&a)[N]) {
	return N;
	//T *b = a;
	//int tipesize = sizeof T;
	//size_t result = 0;
	//while (b(result)) {
	//	result++;
	//}
	//result--;
	//return result;
}



void homework() {
	int input;
	int n;
	cin >> n;
	int *nums = new int[n];
	for (size_t i = 0; i < n; i++) {
		cin >> nums[i];
	}
	int result = 0;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = i + 1; j < n; j++) {
			if (nums[i] > nums[j]) {
				result++;
			}
		}
	}
	cout << result;
	//system("pause");
}

int main() {
	//test();
	homework();
	//system("pause");
}