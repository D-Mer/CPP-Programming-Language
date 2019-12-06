#include <iostream>
#include <windows.h>

#define max(a, b) (a) > (b) ? (a) : (b)
#define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

const int MAX_LEN = 10000;

int* MySort(const int* nums, const size_t len) {
	int* result = new int[len];
	for (size_t i = 0; i < len; i++) {
		result[i] = nums[i];
	}
	for (int i = len - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			if (result[j] > result[i]) {
				result[i] = result[i] ^ result[j];
				result[j] = result[j] ^ result[i];
				result[i] = result[j] ^ result[i];
			}
		}
	}
	return result;
}

void func(size_t n, int* nums) {
	//for (size_t i = 0; i < n; i++) {
	//	cout << nums[i] << ",";
	//}
	//cout << endl;
	int** result = new int*[MAX_LEN];
	size_t count = 0;
	for (size_t i = 0; i < n - 2; i++) {
		if (nums[i] >= 0) {
			break;
		}
		for (size_t j = i + 1; j < n - 1; j++) {
			for (size_t k = j + 1; k < n; k++) {
				if (-nums[i] == nums[j] + nums[k]) {
					int* temp = new int[3]{ nums[i], nums[j], nums[k] };
					if (count) {
						if (result[count - 1][0] == temp[0] && result[count - 1][1] == temp[1] && result[count - 1][2] == temp[2]) {
							continue;
						}
					}
					result[count] = temp;
					count++;
				}
			}
		}
	}

	if (count == 0) {
		cout << -1;
		return;
	}
	cout << '[' << result[0][0] << ',' << result[0][1] << ',' << result[0][2] << ']';
	for (size_t i = 1; i < count; i++) {
		cout << ",[" << result[i][0] << ',' << result[i][1] << ',' << result[i][2] << ']';
	}
}

void homework() {
	size_t n;
	cin >> n;
	if (n == 0) {
		cout << -1;
		return;
	}
	int* nums = new int[n];
	for (size_t i = 0; i < n; i++) {
		cin >> nums[i];
	}
	func(n, MySort(nums, n));
}

int main() {
	homework();
	//system("pause");
	//Sleep(1000);
}