#ifndef DATABASE_H
#define DATABASE_H 1

#include <iostream>
#include <jdbc.h>
#include <memory>
#include <vector>

class DataBase {
public:
	DataBase() = delete;
	explicit DataBase(const std::string &);

	DataBase(const DataBase &) = delete;
	DataBase &operator=(const DataBase &) = delete;
		
	~DataBase() {}

	void print();

	template <typename... Args>
	std::string get(const std::string &, Args... args);

	template <typename... Args>
	int insert(Args...);
	
	bool exists(const std::string &, const std::string &);

private:

	// package parameters for options
	template <typename... Args>
	inline std::string package_(Args...);

	template <typename... Args>
	inline std::string package_(const std::string &, Args...); 
	template <typename... Args>
	inline std::string package_(const char *, Args...); 

	inline std::string package_(const std::string &);
	inline std::string package_(const char *);

	std::shared_ptr<sql::Connection> conn_;
	std::shared_ptr<sql::Statement> stmt_;
	std::string table_name_;
	std::vector<std::string> table_index_;
};

#include "database.tcc"

#endif // DATABASE_H 
