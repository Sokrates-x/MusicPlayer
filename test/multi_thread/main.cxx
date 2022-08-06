#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include "thread_pool.h"

int i, j, k, l;

std::thread::id trivil(int & li, int i, int &&ri) {

	auto id = std::this_thread::get_id();
	std::stringstream ss;
	ss << id;
	std::string tmp;
	ss >> tmp;
	std::string str = "Thread_ID_" + tmp;
	std::ofstream os;
	os.open(str);
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
	auto f1 = pool.submit(trivil, i, 0, 0);
	auto f2 = pool.submit(trivil, j, 0, 0);
	auto f3 = pool.submit(trivil, k, 0, 0);
	auto f4 = pool.submit(trivil, l, 0, 0);
	std::cout << f1.get() << std::endl;
	std::cout << f2.get() << std::endl;
	std::cout << f3.get() << std::endl;
	std::cout << f4.get() << std::endl;
//	pool.finish();	

	return 0;
}
