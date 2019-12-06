#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <windows.h>
#include <iterator>//����output.cpp�����õģ������������������������
#include <limits>//����variable.cpp�����õģ���ȡһЩ�������͵�����
#include <locale.h>


using namespace std;

enum Chess {
	O = 'O',
	X = 'X'
};

enum Result {
	O_Win = 'O',
	X_Win = 'X',
	Dogfall = 'D'
};

map<Result, string> msg = {
	{O_Win, "O Success"},
	{X_Win, "X Success"},
	{Dogfall, "Dogfall"}
};

class Game {
private:
	int width;
	int win_len;
	Chess board[100][100];
	pair<int, int> finalChess;
public:
	Game(int width, int win_len) {
		this->width = width;
		this->win_len = win_len;
	}

	void lay(int x, int y, Chess p) {
		board[x][y] = p;
		finalChess.first = x;
		finalChess.second = y;
	}

	Result getResult() {
		int min_bound = win_len / 2;
		int max_bound = min_bound - (win_len % 2 == 0);
		Result result = Result::Dogfall;
		bool win_flag = false;
		int x, y;
		x = finalChess.first;
		y = finalChess.second;
		Chess chess = board[x][y];
		for (int i = 0; i < win_len; i++) {
			//�жϺ���
			if (((y + i) >= (win_len - 1)) && ((y + i) < width)) {
				int j;
				for (j = 0; j < win_len; j++) {
					if (board[x][y + i - j] != chess) {
						break;
					}
				}
				if (j == win_len) {
					result = Result(chess);
					return result;
				}
			}
			//�ж�����
			if (((x + i) >= (win_len - 1)) && ((x + i) < width)) {
				int j;
				for (j = 0; j < win_len; j++) {
					if (board[x + i - j][y] != chess) {
						break;
					}
				}
				if (j == win_len) {
					result = Result(chess);
					return result;
				}
			}
			//�ж�����б��
			if (((x + i) >= (win_len - 1)) && ((x + i) < width)
				&& ((y + i) >= (win_len - 1)) && ((y + i) < width)) {
				int j;
				for (j = 0; j < win_len; j++) {
					if (board[x + i - j][y + i - j] != chess) {
						break;
					}
				}
				if (j == win_len) {
					result = Result(chess);
					return result;
				}
			}
			//�ж�����б��
			if (((x + i) > (win_len - 1)) && ((x + i) < width)
				&& ((y - i) >= 0) && ((y - i) <= width - win_len)) {
				int j;
				for (j = 0; j < win_len; j++) {
					if (board[x + i - j][y - i + j] != chess) {
						break;
					}
				}
				if (j == win_len) {
					result = Result(chess);
					return result;
				}
			}
		}
		return result;
	}
};

int main() {
	int width, win_len;
	cin >> width >> win_len;
	int x, y;
	Game game(width, win_len);
	bool isO = true;
	while (cin >> x >> y) {
		game.lay(x, y, isO ? Chess::O : Chess::X);
		isO = !isO;
	}
	cout << msg[game.getResult()];
	//system("pause");
}