#include "database.h"

#include <exception>
#include <sstream>
#include <iostream>
#include <functional>
#include <iterator>
#include <utility>

template <typename... Args>
std::string DataBase::package_(Args&&...) {
	throw std::runtime_error("Invalid Input in DataBase::package_()\
		parms. must be const char * or const std::string &");
}

template <typename... Args>
std::string DataBase::package_(const std::string &str, Args&&... args) {
	return str + " " + package_(std::forward<Args>(args)...);	
}

template <typename... Args>
std::string DataBase::package_(const char *str, Args&&... args) {
	return std::string(str) + " " + package_(std::forward<Args>(args)...);	
}

std::string DataBase::package_(const std::string &str) {
	return str;
}

std::string DataBase::package_(const char *str) {
	return str;	
}

// add to table
template <typename... Args>
int DataBase::insert(Args&&... args) {

	std::string str = package_(std::forward<Args>(args)...);
	std::istringstream in(str);

	std::string	name, val;
	std::vector<std::string> values;
	std::string pstr = "INSERT INTO ";	
	pstr += table_name_;
	pstr += " (";
	std::string pstr_suff = ") VALUE (";

	while (in >> name >> val) {
		auto iter = std::find(table_index_.begin(), table_index_.end(),
			name);
		if (iter == table_index_.end()) {
			throw std::runtime_error("Can NOT Find " + name + " in table "
				+ table_name_);
		}
		pstr += name;
		pstr += ", ";
		pstr_suff += "?, ";
		values.push_back(val);
	}

	pstr.pop_back();
	pstr.pop_back();
	pstr += pstr_suff;
	pstr.pop_back();
	pstr.pop_back();
	pstr += ")";

	std::shared_ptr<sql::PreparedStatement> pstmt(
		conn_->prepareStatement(pstr));
	
	int i = 1;
	for (auto m : values)
		pstmt->setString(i++, m);	

	pstmt->execute();

	return 0;
}

template <typename... Args>
std::string DataBase::get(const std::string &what, Args&&... args){
	std::string str = package_(std::forward<Args>(args)...);
	std::istringstream in(str);
	std::string sstr = "SELECT " + what + " FROM " + table_name_ + 
		" WHERE ";
	std::string name, operation, val;
	while (in >> name >> operation >> val) {
		sstr += name;
		sstr += " " + operation;
		sstr += " '" + val + "'";
		sstr += " AND ";
	}
	sstr.pop_back();
	sstr.pop_back();
	sstr.pop_back();
	sstr.pop_back();
	sstr.pop_back();

	std::shared_ptr<sql::ResultSet> res(stmt_->executeQuery(sstr));
	if (!res->next()) 
		throw std::runtime_error("Not Found");
	std::string res_str = res->getString(1);
	if (res->next())
		throw std::runtime_error("Too Much Found");
	return res_str;
}
