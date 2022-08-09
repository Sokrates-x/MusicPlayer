add_library(Database database.cxx)


target_link_libraries(Database PUBLIC
						"/lib64/libmysqlcppconn.so"
						)

target_include_directories(Database PUBLIC
						"${PROJECT_BINARY_DIR}"
						"${PROJECT_SOURCE_DIR}"
						/usr/include/mysql-cppconn/mysql
						)
