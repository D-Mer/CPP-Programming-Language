#include <iostream>
#include <iomanip>
#include <windows.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

using namespace std;

const int MAX_LEN = 10000;

template<class T>
void clear(T* t, size_t bits) {
	for (size_t i = 0; i < bits; i++) {
		t[i] = 0;
	}
}

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
	int p = 0;//截了几段的计数
	int rawlen = strlen(raw);
	int seplen = strlen(seperator);
	int maxsubnum = rawlen / seplen + 3;
	char** result = new char*[maxsubnum];
	const char* buf = raw;
	for (size_t i = 0; i < maxsubnum; i++) {
		result[i] = new char[maxsublen];
	}
	size_t i = 0;//和分隔符比较的计数
	size_t currentlen = 0;//当前段的长度
	while (*buf != '\0' || strlen(buf) > seplen) {
		//循环匹配，如果退出时i==len2则说明匹配成功
		for (i = 0; i < seplen; i++) {
			if (buf[i] != seperator[i]) {
				break;
			}
		}
		if (i == seplen) {
			//复制截出的一段并保存
			size_t j = 0;
			for (j = 0; j < currentlen; j++) {
				result[p][j] = raw[j];
			}
			result[p][j] = '\0';

			//初始化滑动变量
			buf += seplen;
			raw = buf;
			p++;
			currentlen = 0;
		} else {//否则继续前进
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

char* dtos(double d, int i) {
	char* s = new char[50];
	if (i == 0) {
		sprintf_s(s, 100, "%.0f", d);
	} else {
		sprintf_s(s, 100, "%.4f", d);
	}
	return s;
}

template<class T> struct Matrix {
	int n;
	int m;
	T*** matrix;
};

double* addnum(double* a, double* b){
	double* d = new double[100];
	*d = *a + *b;
	return d;
}

char* addchar(char* a, char* b) {
	char* result = new char[100];
	clear(result, 100);
	int i = 0, j = 0;
	int addcount = 0;
	int p = 0;
	bool exist = false;
	while (a[i]) {
		while (result[p]) {
			if (result[p] == a[i]) {
				exist = true;
				p = 0;
				break;
			}
			p++;
		}
		if (!exist) {
			result[addcount] = a[i];
			addcount++;
		}
		p = 0;
		exist = false;
		i++;
	}
	exist = false;
	p = 0;
	while (b[j]) {
		while (result[p]) {
			if (result[p] == b[j]) {
				exist = true;
				p = 0;
				break;
			}
			p++;
		}
		if (!exist) {
			result[addcount] = b[j];
			addcount++;
		}
		p = 0;
		exist = false;
		j++;
	}
	return result;
}

double* mulnum(double* a, double* b) {
	double* d = new double[100];
	clear(d, 100);
	*d = *a * *b;
	return d;
}

char* mulchar(char* a, char* b) {
	char* result = new char[100];
	clear(result, 100);
	int i = 0;
	while (a[i]) {
		result[i] = a[i];
		i++;
	}
	int j = 0;
	while (b[j]) {
		result[i + j] = b[j];
		j++;
	}
	result[i + j] = 0;
	return result;
}

void printMat(Matrix<double>* mat) {
	cout << 1 << endl;
	for (int i = 0; i < mat->n; i++) {
		if ((int)mat->matrix[i][0][0] == mat->matrix[i][0][0]) {
			cout << fixed << setprecision(0) << mat->matrix[i][0][0];
		} else {
			cout << fixed << setprecision(4) << mat->matrix[i][0][0];
		}
		for (int j = 1; j < mat->m; j++) {
			cout << " ";
			if ((int)mat->matrix[i][j][0] == mat->matrix[i][j][0]) {
				cout << fixed << setprecision(0) << mat->matrix[i][j][0];
			} else {
				cout << fixed << setprecision(4) << mat->matrix[i][j][0];
			}
		}
		if (i != mat->n - 1) {
			cout << endl;
		}
	}
}
void printMat(Matrix<char>* mat) {
	cout << -1 << endl;
	for (int i = 0; i < mat->n; i++) {
		cout << mat->matrix[i][0];
		for (int j = 1; j < mat->m; j++) {
			cout << " " << mat->matrix[i][j];
		}
		if (i != mat->n - 1) {
			cout << endl;
		}
	}
}

template<class T>
Matrix<T>* MatMul(const Matrix<T>* mat1, const Matrix<T>* mat2, T* (* add)(T*, T*), T* (* mul)(T* ,T*)) {
	Matrix<T>* result = new Matrix<T>;
	result->n = mat1->n;
	result->m = mat2->m;
	result->matrix = new T**[50];
	for (size_t i = 0; i < 50; i++) {
		result->matrix[i] = new T*[50];
		for (size_t j = 0; j < 50; j++) {
			result->matrix[i][j] = new T[100];
			for (size_t k = 0; k < 100; k++) {
				result->matrix[i][j][k] = 0;
			}
		}
	}
	T* temp = new T[100];
	clear(temp, 100);
	T* test = new T[100];
	clear(test, 100);
	for (size_t i = 0; i < mat1->n; i++) {
		for (size_t j = 0; j < mat2->m; j++) {
			for (size_t k = 0; k < mat1->m; k++) {
				T* a = mat1->matrix[i][k];
				T* b = mat2->matrix[k][j];
				test = mul(mat1->matrix[i][k], mat2->matrix[k][j]);
				temp = add(temp, test);
				clear(test, 100);
			}
			for (size_t x = 0; x < 100; x++) {
				result->matrix[i][j][x] = temp[x];
			}
			clear(temp, 100);
		}
	}
	//printMat(result);
	return result;
}

Matrix<double>* makenumMat(char*** mat, int n, int m) {
	Matrix<double>* numMat = new Matrix<double>();
	numMat->n = n;
	numMat->m = m;
	numMat->matrix = new double**[50];
	for (int i = 0; i < n; i++) {
		numMat->matrix[i] = new double*[50];
		for (int j = 0; j < m; j++) {
			numMat->matrix[i][j] = new double[1];
			numMat->matrix[i][j][0] = (double)atof(mat[i][j]);
		}
	}
	return numMat;
}

Matrix<char>* makecharMat(char*** mat, int n, int m) {
	Matrix<char>* charMat = new Matrix<char>();
	charMat->matrix = new char**[n];
	charMat->n = n;
	charMat->m = m;
	for (int i = 0; i < n; i++) {
		charMat->matrix[i] = new char*[50];
		for (int j = 0; j < m; j++) {
			charMat->matrix[i][j] = new char[50];
			charMat->matrix[i][j] = mat[i][j];
		}
	}
	return charMat;
}



void homework() {
	int type1, type2;
	int n1, m1;
	int n2, m2;
	cin >> type1 >> n1 >> m1;
	getchar();
	char* input = new char[100];
	char** words = new char*[50];
	for (size_t i = 0; i < 50; i++) {
		words[i] = new char[100];
	}
	char*** inputMat1 = new char**[50];
	for (size_t i = 0; i < n1; i++) {
		inputMat1[i] = new char*[50];
		cin.getline(input, MAX_LEN);
		words = splitchars(input, " ", 100);
		for (size_t j = 0; j < m1; j++) {
			inputMat1[i][j] = words[j];
		}
	}
	getchar();//输入换了一行
	cin >> type2 >> n2 >> m2;
	getchar();
	char*** inputMat2 = new char**[50];
	for (size_t i = 0; i < n2; i++) {
		inputMat2[i] = new char*[50];
		cin.getline(input, MAX_LEN);
		words = splitchars(input, " ", 100);
		for (size_t j = 0; j < m2; j++) {
			inputMat2[i][j] = words[j];
		}
	}

	if (type1 == 1 && type2 == 1) {
		Matrix<double>* mat1 = makenumMat(inputMat1, n1, m1);
		Matrix<double>* mat2 = makenumMat(inputMat2, n2, m2);
		//printMat(mat1);
		//printMat(mat2);
		double* (*add)(double*, double*) = addnum;
		double* (*mul)(double*, double*) = mulnum;
		Matrix<double>* result = MatMul(mat1, mat2, add, mul);
		printMat(result);
	} else {
		Matrix<char>* mat1 = makecharMat(inputMat1, n1, m1);
		Matrix<char>* mat2 = makecharMat(inputMat2, n2, m2);
		//printMat(mat1);
		//printMat(mat2);
		char* (*add)(char*, char*) = addchar;
		char* (*mul)(char*, char*) = mulchar;
		Matrix<char>* result = MatMul(mat1, mat2, add, mul);
		printMat(result);
	}



}

int main() {
	//test();
	homework();
	//system("pause");
	//Sleep(1000);
}