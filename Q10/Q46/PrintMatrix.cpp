#include <iostream>
#include <windows.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

const int MAX_LEN = 1000;

inline int getNum(int x, int y, int xNum, int yNum) {
	return y + 1 + x * yNum;
}

void func(int xNum, int yNum) {
	int flag = 0;
	int top = 0, right = yNum - 1, bottom = xNum - 1, left = 0;
	int* result = new int[xNum * yNum + 1];
	result[xNum * yNum] = -1;
	int p = 0;
	while (p < xNum * yNum) {
		switch (flag) {
		case 0:
			for (int i = left; i <= right; i++) {
				result[p] = getNum(top, i, xNum, yNum);
				//cout << " " << result[p];
				p++;
			}
			top++;
			break;
		case 1:
			for (int i = top; i <= bottom; i++) {
				result[p] = getNum(i, right, xNum, yNum);
				//cout << " " << result[p];
				p++;
			}
			right--;
			break;
		case 2:
			for (int i = right; i >= left; i--) {
				result[p] = getNum(bottom, i, xNum, yNum);
				//cout << " " << result[p];
				p++;
			}
			bottom--;
			break;
		case 3:
			for (int i = bottom; i >= top; i--) {
				result[p] = getNum(i, left, xNum, yNum);
				//cout << " " << result[p];
				p++;
			}
			left++;
			break;
		default:
			break;
		}
		flag++;
		flag %= 4;
	}
	cout << *result;
	result++;
	while (*result != -1) {
		cout << " " << *result;
		result++;
	}
}

void homework() {
	int xNum, yNum;
	cin >> xNum >> yNum;
	func(xNum, yNum);
}

int main() {
	homework();
	//system("pause");
	//Sleep(1000);
}