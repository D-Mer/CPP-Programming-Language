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
#include <iterator>//这是output.cpp里引用的，可以做输入输出的流迭代器
#include <limits>//这是variable.cpp里引用的，获取一些变量类型的属性
#include <locale.h>

# define max(a, b) (a) > (b) ? (a) : (b)
# define min(a, b) (a) < (b) ? (a) : (b)

using namespace std;

vector<string> split(const string input, const string seperator) {
	string loop = input + seperator;
	vector<string> items;
	int p;
	while ((p = loop.find(seperator)) != -1) {
		items.push_back(loop.substr(0, p));
		loop = loop.substr(p + seperator.length());
	}
	return items;
}

class Hero {
protected:
	int hp;
	int atk;
	string name;
	Hero(int hp, int atk, string name) : hp(hp), atk(atk), name(name) {}
public:
	virtual void roundStart() {}
	virtual void roundEnd() {}
	virtual void attack(Hero* enemy) {
		enemy->beHurt(this);
	}
	virtual void beHurt(Hero* enemy) {
		this->hp -= enemy->atk;
	}
	virtual bool isAlive() {
		return hp > 0;
	}
	virtual void print() {
		cout << name << " " << atk << " " << hp << endl;
	}
	enum Type {
		Warrior = 1,
		Magician = 2,
		Leader = 3
	};
};

class Warrior : public Hero {
public:
	Warrior() : Hero(12, 2, "Warrior") {}
	void roundEnd() {
		if (isAlive()) {
			hp++;
		}
	}
};

class Magician : public Hero {
private:
	bool shield = true;
public:
	Magician() : Hero(2, 6, "Magician") {}
	void beHurt(Hero* enemy) {
		if (shield) {
			shield = false;
		} else {
			Hero::beHurt(enemy);
		}
	}
};

class Leader : public Hero {
public:
	Leader() : Hero(6, 6, "Leader") {}
	void roundEnd() {
		if (isAlive()) {
			atk++;
		}
	}
};

class Team {
private:
	int itr;
	vector<Hero*> heros;

public:
	void addHero(Hero* hero) {
		heros.push_back(hero);
	}
	void knockOut() {
		itr++;
	}
	Hero* getFirst() {
		return heros[itr];
	}
	bool isUnderdog() {
		return itr == heros.size();
	}
	void printAlive() {
		for (int i = itr; i < heros.size(); i++) {
			heros[i]->print();
		}
	}
};

class Game {
private:
	int n;
	Team team1;
	Team team2;

public:
	Game(int n) : n(n) {}
	void add(Hero::Type type, int team) {
		Hero* hero = NULL;
		switch (type) {
		case Hero::Warrior:
			hero = new Warrior();
			break;
		case Hero::Magician:
			hero = new Magician();
			break;
		case Hero::Leader:
			hero = new Leader();
			break;
		default:
			break;
		}
		if (team == 1) {
			team1.addHero(hero);
		} else {
			team2.addHero(hero);
		}
	}

	void fight(Hero* h1, Hero* h2) {
		while (h1->isAlive() && h2->isAlive()) {
			h1->roundStart();
			h2->roundStart();
			h1->attack(h2);
			h2->attack(h1);
			h1->roundEnd();
			h2->roundEnd();
		}
	}

	void play() {
		Hero* h1;
		Hero* h2;
		while (!team1.isUnderdog() && !team2.isUnderdog()) {
			h1 = team1.getFirst();
			h2 = team2.getFirst();
			fight(h1, h2);
			if (!h1->isAlive()) {
				team1.knockOut();
			}
			if (!h2->isAlive()) {
				team2.knockOut();
			}
		}
	}

	void printResult() {
		if (team1.isUnderdog() && team2.isUnderdog()) {
			cout << "All Dead" << endl;
		}
		if (team2.isUnderdog()) {
			team1.printAlive();
		} else if (team1.isUnderdog()) {
			team2.printAlive();
		}
	}
};


int main() {
	int n = 0;
	cin >> n;
	getchar();
	int input;
	Hero::Type type;
	Game game(n);
	for (int i = 0; i < n; i++) {
		cin >> input;
		type = Hero::Type(input);
		game.add(type, 1);
	}
	for (int i = 0; i < n; i++) {
		cin >> input;
		type = Hero::Type(input);
		game.add(type, 2);
	}
	game.play();
	game.printResult();
	//system("pause");
	return 0;
}