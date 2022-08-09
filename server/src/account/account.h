#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include "database.h"

class Account {
public:
	Account() = delete;
	Account(const std::string &account, const std::string &passwd, 
		const std::string &name, const std::string &stat = "", 
		const std::string &birth = "");
	~Account() {}

	void print_db() {
		db_.print();
	}
private:
	DataBase db_;	
	long long id_;
};

#endif
