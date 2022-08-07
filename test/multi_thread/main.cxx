#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iterator>
#include <functional>
#include "thread_pool.h"

std::thread::id trivil(int & li, int i, int &&ri) {

	auto id = std::this_thread::get_id();
	std::stringstream ss;
	ss << id;
	std::string tmp;
	ss >> tmp;
	std::string str = "Thread_ID_" + tmp;
	std::ofstream os;
	os.open(str, std::ios::app | std::ios::out);
	for (int n = 0; n < 1000; ++n) {
		++li;
		++i;
		++ri;
		os << li << i << ri << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	os.close();
	return id;
}

int main(int, char **)
{
	
	ThreadPool<std::thread::id(int &, int, int &&),
		int &, int, int &&> pool;

	// this code need gcc -O3 & i don't know why
	std::vector<std::future<std::thread::id>> vec_futures;

	thread_local int i = 0;	
	for (int i = 0; i < 100; ++i) 
		vec_futures.push_back(pool.submit(trivil, i, 0, 0));

	for (auto &m : vec_futures) 
		std::cout << m.get() << std::endl;

	pool.finish();

	std::cout << i << std::endl;
	return 0;
}
