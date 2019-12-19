#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <set>
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

class Task {
protected:
	int id;
	string name;//名字
	string type;//类型
	int priority;//优先级
	int arriveTime;//任务到达时间
	int carryTime;//任务执行时间
	int startTime;//任务开始时间
	bool finished;//是否完成

public:
	Task(int id, string name, int priority, int arriveTime, int carryTime) {
		this->id = id;
		this->name = name;
		this->priority = priority;
		this->arriveTime = arriveTime;
		this->carryTime = carryTime;
		this->startTime = -1;
		this->finished = false;
	}

	//结束动作
	void finish() {
		finished = true;
	}

	//给cpu判断任务是否结束来调用finish()动作
	bool isFinished(int time) {
		return (time - startTime) >= carryTime;
		//return finished;
	}

	//判断任务优先级
	bool HighThan(Task* t, string mode, int time) {
		if (mode == "PSA") {
			if (this->priority < t->priority) {
				return true;
			} else if (this->priority == t->priority) {
				return this->id < t->id;
			} else {
				return false;
			}
		} else if (mode == "HRRF") {
			double current = (time - arriveTime + carryTime) / (carryTime + 0.0);
			double another = (time - t->arriveTime + t->carryTime) / (t->carryTime + 0.0);
			if (current > another) {
				return true;
			} else if (current == another) {
				return this->id < t->id;
			} else {
				return false;
			}
		} else {
			cout << "no such mode : " << mode << endl;
			return false;
		}
	}

	//任务开始动作
	void start(int time) {
		startTime = time;
	}

	//打印加载信息
	virtual void printLoad(int time, int coreId) {
		cout << "task " << id << " load: time " << time << " coreId " << coreId << " name " << name << " type " << type << " priority " << priority << endl;
	}

	//打印执行内容信息，子类有各自的实现
	virtual void printExecute(int time, int coreId) {
		cout << "task " << id << " execute: time " << time << " coreId " << coreId << endl;
	}

	//打印结束信息
	virtual void printFinish(int time, int coreId) {
		cout << "task " << id << " finish: time " << time << " coreId " << coreId << endl;
	}
	friend class Driver;
};

class LoadDatabase : public Task {
public:
	LoadDatabase(int id, string name, int priority, int arriveTime, int carryTime) : Task(id, name, priority, arriveTime, carryTime) {
		this->type = "LoadDatabase";
	}

	virtual void printExecute(int time, int coreId) {
		Task::printExecute(time, coreId);
		cout << "task " << id << " --- Load driver" << endl;
		cout << "task " << id << " --- Establish a database connection" << endl;
		cout << "task " << id << " --- Create a Statement object" << endl;
		cout << "task " << id << " --- Execute SQL" << endl;
		cout << "task " << id << " --- Close the database" << endl;
	}
	friend class Driver;
};

class ETL : public Task {
public:
	ETL(int id, string name, int priority, int arriveTime, int carryTime) : Task(id, name, priority, arriveTime, carryTime) {
		this->type = "ETL";
	}

	virtual void printExecute(int time, int coreId) {
		Task::printExecute(time, coreId);
		cout << "task " << id << " --- Read data from a file" << endl;
		cout << "task " << id << " --- Data transform" << endl;
		cout << "task " << id << " --- Load data into the database" << endl;
	}
	friend class Driver;
};

class DataAnalyze : public Task {
public:
	DataAnalyze(int id, string name, int priority, int arriveTime, int carryTime) : Task(id, name, priority, arriveTime, carryTime) {
		this->type = "DataAnalyze";
	}

	virtual void printExecute(int time, int coreId) {
		Task::printExecute(time, coreId);
		cout << "task " << id << " --- Finding the center point" << endl;
		cout << "task " << id << " --- Data Classification" << endl;
		cout << "task " << id << " --- Data comparison" << endl;
		cout << "task " << id << " --- Data Display" << endl;
	}
	friend class Driver;
};

class CPU {
public:
	int id;
	Task* carrying;
	friend class Driver;

	CPU(int id) : id(id), carrying(nullptr) {}

	//加载任务
	void loadTask(Task* task, int time) {
		carrying = task;
		task->start(time);
		carrying->printLoad(time, id);
		carrying->printExecute(time, id);
	}

	//执行任务中
	void execute(int time) {
		//如果没有在执行任务则空闲
		if (carrying == nullptr) {
			return;
		} else {
			//如果任务结束则调用结束动作
			if (carrying->isFinished(time)) {
				carrying->finish();
				carrying->printFinish(time, id);
				carrying = nullptr;
			}
		}
	}

	//判断是否空闲
	bool isFree() {
		return (carrying == nullptr);
	}
};

class Driver {
public:
	int clock;
	string mode;
	vector<CPU*> cpus;
	vector<Task*> tasks;

	//时钟驱动
	void run() {
		loadTask();
		while (!allTaskFinished()) {
			execute();//先打印finish
			loadTask();//再打印load
			clock++;
		}
	}

	//给空闲CPU加载任务
	void loadTask() {
		int freeTaskIndex;
		int freeCPUIndex;
		bool flag;
		while ((freeTaskIndex = getFreeTask()) >= 0) {
			if((freeCPUIndex = getFreeCPU()) >= 0) {
				cpus[freeCPUIndex]->loadTask(tasks[freeTaskIndex], clock);
			} else {
				break;
			}
		}
	}

	//所有CPU执行当前任务
	void execute() {
		for (size_t i = 0; i < cpus.size(); i++) {
			cpus[i]->execute(clock);
		}
	}

	//获取下一个空闲CPU
	int getFreeCPU() {
		for (size_t i = 0; i < cpus.size(); i++) {
			if (cpus[i]->isFree()) {
				return i;
			}
		}
		return -1;
	}

	//获取下一个最优先的空闲任务
	int getFreeTask() {
		int high = -1;
		high = getNextTaskStartFrom(0);
		if (high < 0) {
			return high;
		}
		//比较所有空闲任务的优先级，获取最优先任务
		int next = high + 1;
		while ((next = getNextTaskStartFrom(next)) >= 0) {
			if (tasks[next]->HighThan(tasks[high], mode, clock)) {
				high = next;
			}
			next++;
		}
		return high;
	}

	//获取当前下标开始的空闲任务
	int getNextTaskStartFrom(int n) {
		for (size_t i = n; i < tasks.size(); i++) {
			if (tasks[i]->startTime < 0 && tasks[i]->arriveTime <= clock) {
				return i;
			}
		}
		return -1;
	}

	//判断是否还有空闲任务
	bool allTaskFinished() {
		for (size_t i = 0; i < tasks.size(); i++) {
			if (!tasks[i]->finished) {
				return false;
			}
		}
		return true;
	}

};


int main() {
	int n;
	string mode;
	int m;
	string input;
	vector<string> params;
	getline(cin, input);
	params = split(input, " ");
	n = stoi(params[0]);
	mode = params[1];
	m = stoi(params[2]);

	//初始化CPU
	Driver d;
	for (int i = 0; i < n; i++) {
		d.cpus.push_back(new CPU(i));
	}

	//初始化模式
	d.mode = mode;

	//初始化任务
	for (int i = 0; i < m; i++) {
		getline(cin, input);
		params = split(input, " ");
		int id = stoi(params[0]);
		string name = params[1];
		int type = stoi(params[2]);
		int priority = stoi(params[3]);
		int arriveTime = stoi(params[4]);
		int carryTime = stoi(params[5]);
		switch (type) {
		case 0:
			d.tasks.push_back(new LoadDatabase(id, name, priority, arriveTime, carryTime));
			break;
		case 1:
			d.tasks.push_back(new ETL(id, name, priority, arriveTime, carryTime));
			break;
		case 2:
			d.tasks.push_back(new DataAnalyze(id, name, priority, arriveTime, carryTime));
			break;
		default:
			break;
		}
	}

	d.run();
	return 0;
}