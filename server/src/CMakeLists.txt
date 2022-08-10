cmake_minimum_required(VERSION 3.10)

project(MusicServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(database)
add_subdirectory(account)
add_subdirectory(multi_thread)
add_subdirectory(network)

add_executable(Main main.cxx)

target_link_libraries(Main PUBLIC Database
								  Account	
								  Network
								  Connect
						)

target_include_directories(Database PUBLIC
						"${PROJECT_BINARY_DIR}"
						"${PROJECT_SOURCE_DIR}"
						"${PROJECT_SOURCE_DIR}/account"
						"${PROJECT_SOURCE_DIR}/multi_thread/thread_pool"
						"${PROJECT_SOURCE_DIR}/multi_thread/thread_safe_queue"
						"${PROJECT_SOURCE_DIR}/network/boot"
						"${PROJECT_SOURCE_DIR}/network/connect"
						)
