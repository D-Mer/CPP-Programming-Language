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

class Plane {
private:
	int take_off = 0;//�����ʱ
	int take_off_time = 0;//���ʱ��
	int task = 0;//������ʱ
	int landing = 0;//������ʱ
	int landing_time = 0;//����ʱ��
	int priority = 0;//���ȼ�
	int no = 0;//���
	string type = "";//����
public:
	Plane(int no, string type) throw (string) {
		if (type == "helicopter") {
			init(1, 0, 1);
			priority = 3;
		} else if (type == "battleplane") {
			init(2, 0, 2);
			priority = 2;
		} else if (type == "transportplane") {
			init(3, 0, 3);
			priority = 1;
		} else {
			throw "Error type!";
		}
		this->type = type;
		this->no = no;
	}
	void init(int take_off, int task, int landing) {
		this->take_off = take_off;
		this->task = task;
		this->landing = landing;
	}
	int get_take_off() {
		return take_off;
	}
	int get_take_off_time() {
		return take_off_time;
	}
	int get_task() {
		return task;
	}
	int get_landing() {
		return landing;
	}
	int get_landing_time() {
		return landing_time;
	}
	int get_no() {
		return no;
	}
	string get_type() {
		return type;
	}
	int getPriority() {
		return priority;
	}
	void print_normal() {
		cout << "p" << no << " " << type << " " << take_off << " " << task << " " << landing << endl;
	}
	void print_schedule() {
		cout << "p" << no << " " << take_off_time << " " << landing_time << endl;
	}
	void taking_off(int time) {
		this->take_off_time = time;
	}
	void land(int time) {
		this->landing_time = time + this->landing;
	}
};

class Carrier {
private:
	int clock = 0;
	map<int, Plane*> planes;
	vector<pair<Plane*, int>> arrivedList;
	vector<Plane*> landingList;
	vector<pair<Plane*, int>> landFirstList;
	vector<pair<Plane*, int>> taking_offList;
	vector<Plane*> taskingList;

public:
	void add(int no, string type) {
		planes[no] = new Plane(no, type);
	}

	void set(int no, int take_off, int task, int landing) {
		planes[no]->init(take_off, task, landing);
	}

	void join(int no, int time) {
		vector<pair<Plane*, int>>::iterator itr = taking_offList.begin();
		Plane* toTakeOff = planes[no];
		Plane* temp;
		while (itr != taking_offList.end()) {
			temp = itr->first;
			if (time > itr->second) {//�ȵ�ǰ���ɷɻ��ٷ���ֱ���ж���һ�ܴ��ɷɻ�
				itr++;
				continue;
			} else if (time == itr->second) {
				//����ʱ����ͬ�����ȼ��ߵ��ȷ�
				if (toTakeOff->getPriority() > temp->getPriority()) {
					taking_offList.insert(itr, pair<Plane*, int>(toTakeOff, time));
					return;
				}
				//������ȼ���ͬ����С���ȷ�
				if (toTakeOff->getPriority() == temp->getPriority()) {
					if (toTakeOff->get_no() < temp->get_no()) {
						taking_offList.insert(itr, pair<Plane*, int>(toTakeOff, time));
						return;
					}
				}
			} else {
				//�ȵ�ǰ���ɷɻ����������֮ǰ����
				taking_offList.insert(itr, pair<Plane*, int>(toTakeOff, time));
				return;
			}
			itr++;
		}
		taking_offList.push_back(pair<Plane*, int>(toTakeOff, time));
	}

	void landfirst(int no, int time) {
		landFirstList.push_back(pair<Plane*, int>(planes[no], time));
	}

	void print(string command) {
		if (command == "normal") {
			map<int, Plane*>::iterator itr = planes.begin();
			while (itr != planes.end()) {
				itr->second->print_normal();
				itr++;
			}
		} else if (command == "schedule") {
			vector<Plane*>::iterator itr = landingList.begin();
			while (itr != landingList.end()) {
				(*itr)->print_schedule();
				itr++;
			}
		} else {
			cout << "No such command" << endl;
		}
	}

	void add_arrived(Plane* plane, int take_off_time) {
		vector<pair<Plane*, int>>::iterator itr = arrivedList.begin();
		Plane* temp;
		// ����ʱ��Ӧ�������ʱ�������ִ��ʱ��
		take_off_time += plane->get_take_off() + plane->get_task();
		while (itr != arrivedList.end()) {
			temp = itr->first;
			// �����絽��ķɻ�֮ǰ�����������λ
			if (take_off_time < itr->second) {
				arrivedList.insert(itr, pair<Plane*, int>(plane, take_off_time));
				return;
			} else if (take_off_time == itr->second) {
				// ����ʱ����ͬ�����ȼ���(�������ȼ���������ȼ��෴)���Ƚ���
				if (plane->getPriority() < temp->getPriority()) {
					arrivedList.insert(itr, pair<Plane*, int>(plane, take_off_time));
					return;
				} else if (plane->getPriority() == temp->getPriority()
					&& plane->get_no() < temp->get_no()) {
					// ������ȼ�Ҳ��ͬ����С���Ƚ���
					arrivedList.insert(itr, pair<Plane*, int>(plane, take_off_time));
					return;
				}
			}
			itr++;
		}
		arrivedList.push_back(pair<Plane*, int>(plane, take_off_time));
	}

	void removeArrived(Plane* plane) {
		for (size_t i = 0; i < arrivedList.size(); i++) {
			if (arrivedList[i].first->get_no() == plane->get_no()) {
				arrivedList.erase(arrivedList.begin() + i);
				break;
			}
		}
	}

	void calculate() {
		int take_p = 0;
		int arrived_p = 0;
		pair<Plane*, int>* taking_off_itr;
		pair<Plane*, int>* arrived_itr;
		do {
			// ��ǰʱ���Ƿ������Ƚ���ָ��
			for (int itr = landFirstList.size() - 1; itr >= 0; itr--) {
				if (landFirstList[itr].second <= clock) {
					landFirstList[itr].first->land(clock);
					landingList.push_back(landFirstList[itr].first);
					clock += landFirstList[itr].first->get_take_off();
					removeArrived(landFirstList[itr].first);
					landFirstList.erase(landFirstList.begin() + itr);
					break;
				}
			}
			// ���ж��Ƿ��зɻ�Ҫ���
			if (take_p < taking_offList.size()) {
				taking_off_itr = &taking_offList[take_p];
				// ����ǰʱ�䲻����������ɵķɻ������
				if (taking_off_itr->second <= clock) {
					taking_off_itr->first->taking_off(clock);
					add_arrived(taking_off_itr->first, clock);
					clock += taking_off_itr->first->get_take_off();
					take_p++;
					continue;
				}
			}
			// ����ǰʱ��û��Ҫ��ɵķɻ����ж���û��Ҫ����ķɻ�
			else if (arrived_p < arrivedList.size()) {
				// �����ǳ�ʼ������ķɻ�(�ʼ��֪���ĸ��ɻ��Ƚ���)
				arrived_itr = &arrivedList[arrived_p];
				if (arrived_itr->second <= clock) {
					arrived_itr->first->land(clock);
					landingList.push_back(arrived_itr->first);
					clock += arrived_itr->first->get_landing();
					arrived_p++;
					continue;
				}
			}// �����ǰʱ��û�����Ҳû�н�����clock++
			clock++;
		} while (take_p < taking_offList.size()
			|| arrived_p < arrivedList.size());
	}
};

int main() {
	Carrier carrier;
	int n;
	cin >> n;
	getchar();
	string input;
	vector<string> command;
	for (int i = 0; i < n; i++) {
		int no = 0;
		getline(cin, input);
		command = split(input, " ");
		if (command[0] == "add") {
			no = stoi(command[2].substr(1));
			carrier.add(no, command[1]);
		} else if (command[0] == "set") {
			no = stoi(command[1].substr(1));
			carrier.set(no, stoi(command[2]), stoi(command[3]), stoi(command[4]));
		} else if (command[0] == "join") {
			no = stoi(command[1].substr(1));
			carrier.join(no, stoi(command[2]));
		} else if (command[0] == "landfirst") {
			no = stoi(command[2].substr(1));
			carrier.landfirst(no, stoi(command[1]));
		} else if (command[0] == "normal") {
			break;
		} else if (command[0] == "schedule") {
			break;
		}
	}
	carrier.calculate();
	carrier.print(command[0]);
	//system("pause");
}