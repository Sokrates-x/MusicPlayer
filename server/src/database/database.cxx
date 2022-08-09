#include "database.h"
#include <memory>
#include <exception>

DataBase::DataBase(const std::string &str) : table_name_(str) {
	// get driver
	sql::mysql::MySQL_Driver *driver = 
		sql::mysql::get_mysql_driver_instance();

	// connect options
	sql::ConnectOptionsMap connection_properties;	
	connection_properties["hostName"] = "localhost";
	connection_properties["userName"] = "sokrates";
	connection_properties["password"] = "light";
	connection_properties["OPT_RECONNECT"] = true;

	// connect
	conn_.reset(driver->connect(connection_properties));

	// statement execute
	stmt_.reset(conn_->createStatement());
	stmt_->execute("use music_player");		

	// table index
	std::shared_ptr<sql::ResultSet> res(
		stmt_->executeQuery("DESCRIBE " + table_name_)); 

	while (res->next())
		table_index_.push_back(res->getString(1));
}

void DataBase::print() {

	std::copy(table_index_.cbegin(), table_index_.cend(), 
		std::ostream_iterator<std::string>(std::cout, "\t"));

	std::shared_ptr<sql::ResultSet> res(
		stmt_->executeQuery("SELECT * FROM " + table_name_));

	while (res->next()) {
		for (int i = 1; i <= table_index_.size(); ++i)
			std::cout << res->getString(i) << '\t';
		std::cout << '\n';
	}
}

// exists ?
bool DataBase::exists(const std::string &name, const std::string &val) {
	 
	if (std::find(table_index_.cbegin(), table_index_.cend(), name) ==
		table_index_.cend())
		throw std::runtime_error("Can NOT Find " + name + " in table "
			+ table_name_);

	std::shared_ptr<sql::ResultSet> rset(
		stmt_->executeQuery("SELECT * FROM " + table_name_ + 
		" WHERE (" + name + " = '" + val + "')"));
	if (rset->next())
		return true;
	return false;
}
