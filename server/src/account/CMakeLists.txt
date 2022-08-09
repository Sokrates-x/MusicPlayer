add_library(Account account.cxx)


target_link_libraries(Account PUBLIC Database
						)

target_include_directories(Database PUBLIC
						"${PROJECT_BINARY_DIR}"
						"${PROJECT_SOURCE_DIR}"
						"${PROJECT_SOURCE_DIR}/database"
						)
