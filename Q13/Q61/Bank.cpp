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
#include <iomanip>
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

class MyExcepion {
private:
	int code;
	string msg;
public:
	MyExcepion() {
		this->code = 0;
		this->msg = "";
	}
	MyExcepion(int code) {
		this->code = code;
		this->msg = "";
	}
	MyExcepion(string msg) {
		this->code = 0;
		this->msg = msg;
	}
	MyExcepion(int code, string msg) {
		this->code = code;
		this->msg = msg;
	}
	int getCode() {
		return code;
	}
	string getMessage() {
		return msg;
	}
};

class LessThanZeroException : public MyExcepion {
public:
	LessThanZeroException() : MyExcepion("amount must be greater than zero") {}
};
class UnenoughException : public MyExcepion {
public:
	UnenoughException() : MyExcepion("sumTransactions must be greater than zero") {}
};

class Account {
protected:
	int id;
	double balance;
	string name;
	vector<pair<string, double>> records;
	Account(int id, string name) : id(id), balance(0), name(name) {}

public:
	double getBalance() {
		return balance;
	}

	double getRecordsAllAmount() {
		auto itr = records.begin();
		double total = 0;
		for (; itr != records.end(); itr++) {
			total += (itr->first == "deposit" ? itr->second : -itr->second);
		}
		return total;
	}

	void printAllRecords() {
		double total = 0;
		if (name == "Maxi-Savings Account") {
			return;
		}
		cout << name << endl;
		auto itr = records.begin();
		for (; itr != records.end(); itr++) {
			total += (itr->first == "deposit" ? itr->second : -itr->second);
			cout << "  " << itr->first << " $" << fixed << setprecision(2) << itr->second << endl;
		}
		cout << "Total $" << total << endl << endl;
	}

	void withdraw(double amount) throw(UnenoughException, LessThanZeroException) {
		if (amount <= 0) {
			throw LessThanZeroException();
		}
		if (balance < amount) {
			throw UnenoughException();
		}
		balance -= amount;
		records.push_back(make_pair("withdrawal", amount));
	}
	void deposit(double amount) throw(LessThanZeroException) {
		if (amount <= 0) {
			throw LessThanZeroException();
		}
		balance += amount;
		records.push_back(make_pair("deposit", amount));
	}
	virtual double getInterest() = 0;
	enum Type {
		CheckingAccount = 0,
		SavingAccount = 1,
		MaxAccount = 2
	};
};

class CheckingAccount : public Account {
public:
	CheckingAccount(int id) : Account(id, "Checking Account") {}

	double getInterest() {
		return balance * 0.001;
	}
};

class SavingAccount : public Account {
public:
	SavingAccount(int id) : Account(id, "Savings Account") {}
	double getInterest() {
		if (balance <= 1000) {
			return balance * 0.001;
		} else {
			return 1 + (balance - 1000) * 0.002;
		}
	}
};

class MaxAccount : public Account {
public:
	MaxAccount(int id) : Account(id, "Maxi-Savings Account") {}

	double getInterest() {
		if (balance <= 1000) {
			return balance * 0.02;
		} else if (balance <= 2000) {
			return 20 + (balance - 1000) * 0.05;
		} else {
			return 20 + 50 + (balance - 2000) * 0.1;
		}
	}
};

class Customer {
private:
	string name;
	vector<Account*> accounts;
public:
	Customer(string name) : name(name) {}

	void addAccount(Account* account) {
		accounts.push_back(account);
	}

	int getAccountNum() {
		return accounts.size();
	}

	double totalInterestEarned() {
		double result = 0;
		vector<Account*>::iterator itr = accounts.begin();
		for (; itr != accounts.end(); itr++) {
			result += (*itr)->getInterest();
		}
		return result;
	}

	void printStatement() {
		cout << "Statement for " << this->name << endl << endl;
		double total = 0;
		for (size_t i = 0; i < accounts.size(); i++) {
			total += accounts[i]->getRecordsAllAmount();
			accounts[i]->printAllRecords();
		}
		cout << "Total In All Accounts $" << fixed << setprecision(2) << total << endl;
	}
};

class Bank {
private:
	vector<Account*> accounts;
	map<string, Customer*> customers;

public:
	void createAccount(int type) {
		Account* account = NULL;
		switch (Account::Type(type)) {
		case Account::CheckingAccount:
			account = new CheckingAccount(accounts.size());
			break;
		case Account::SavingAccount:
			account = new SavingAccount(accounts.size());
			break;
		case Account::MaxAccount:
			account = new MaxAccount(accounts.size());
			break;
		default:
			break;
		}
		accounts.push_back(account);
	}

	void createCustomer(string name) {
		Customer* customer = new Customer(name);
		customers[name] = customer;
	}

	void addToCustomer(int index, string name) {
		customers[name]->addAccount(accounts[index]);
	}

	void accountDepposit(int index, double amount) {
		try {
			accounts[index]->deposit(amount);
		} catch (MyExcepion e) {
			cout << e.getMessage() << endl;
		}
	}

	void accountWithdraw(int index, double amount) {
		try {
			accounts[index]->withdraw(amount);
		} catch (MyExcepion e) {
			cout << e.getMessage() << endl;
		}
	}

	void sumTransactions(int index) {
		cout.unsetf(ios::fixed);
		cout << fixed << setprecision(1) << accounts[index]->getBalance() << endl;
	}

	void numberOfAccount(string name) {
		cout.unsetf(ios::fixed);
		cout << customers[name]->getAccountNum() << endl;
	}

	void totalInterestEarned(string name) {
		cout.unsetf(ios::fixed);
		cout << fixed << setprecision(1) << customers[name]->totalInterestEarned() << endl;
	}

	void getStatement(string name) {
		customers[name]->printStatement();
	}

	void bankTotalInserstPaid() {
		double total = 0;
		auto itr = customers.begin();
		for (; itr != customers.end(); itr++) {
			total += itr->second->totalInterestEarned();
		}
		cout << fixed << setprecision(1) << total << endl;
	}

	void customsum() {
		cout << "Customer Summary" << endl;
		auto itr = customers.begin();
		for (; itr != customers.end(); itr++) {
			int num = itr->second->getAccountNum();
			cout << " - " << itr->first << " (" << num << " account" << (num > 1 ? "s" : "") << ")" << endl;
		}
	}

};


int main() {
	string input;
	vector<string> params;
	Bank bank;
	cout.setf(ios::fixed);
	while (true) {
		getline(cin, input);
		params = split(input, " ");
		if (params[0] == "createCustomer") {
			bank.createCustomer(params[1]);
		} else if (params[0] == "createAccount") {
			bank.createAccount(stoi(params[1]));
		} else if (params[0] == "addToCustomer") {
			bank.addToCustomer(stoi(params[1]), params[2]);
		} else if (params[0] == "accountDeposit") {
			bank.accountDepposit(stoi(params[1]), stod(params[2]));
		} else if (params[0] == "accountWithdraw") {
			bank.accountWithdraw(stoi(params[1]), stod(params[2]));
		} else if (params[0] == "sumTransactions") {
			bank.sumTransactions(stoi(params[1]));
		} else if (params[0] == "numberOfAccount") {
			bank.numberOfAccount(params[1]);
		} else if (params[0] == "totalInterestEarned") {
			bank.totalInterestEarned(params[1]);
		} else if (params[0] == "getStatement") {
			bank.getStatement(params[1]);
		} else if (params[0] == "banktotalInserstPaid") {
			bank.bankTotalInserstPaid();
		} else if (params[0] == "customsum") {
			bank.customsum();
		} else if (params[0] == "end") {
			break;
		} else {
			cout << "no such command" << endl;
		}
	}
	//Sleep(1000);
	return 0;
}