#include "account.h"
#include <iostream>
#include <exception>

Account::Account(const std::string &account, const std::string &passwd, 
	const std::string &name, const std::string &stat, 
	const std::string &birth) : db_("user_passwd") {

	if (db_.exists("user_account", account))
		throw std::runtime_error("Account Exists");

	if (stat != "" && birth != "")
		db_.insert("user_name", name, "user_account", account, 
			"user_passwords", passwd, "user_stat", stat, "user_birth",
			birth);
	if (stat != "" && birth == "")
		db_.insert("user_name", name, "user_account", account, 
			"user_passwords", passwd, "user_stat", stat);
	if (stat == "" && birth != "")
		db_.insert("user_name", name, "user_account", account, 
			"user_passwords", passwd, "user_birth", birth);
	if (stat == "" && birth == "")	
		db_.insert("user_name", name, "user_account", account, 
			"user_passwords", passwd);
	id_ = std::stoll(db_.get("user_id", "user_account", "=", account));
	std::cout << id_ << std::endl;
}
