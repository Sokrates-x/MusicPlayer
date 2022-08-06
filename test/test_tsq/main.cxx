#include <thread>
#include <fstream>
#include <future>
#include "thread_safe_queue.h"
#include <iostream>

void push(ThreadSafeQueue<int> *q) {
	std::ofstream os;
	os.open("push");
	for (int i = 0; i < 2000; ++i){
		if (i > 0)
			os << i << std::endl;
		q->push(i);	
	}
	os.close();
}

void try_pop(ThreadSafeQueue<int> *q) {
	std::ofstream os;
	os.open("try_pop_data");
	for (int i = 0; i < 1000; ++i) {
		auto p = q->try_pop().get();
		if (p)
			os << *p << std::endl;
	}
	os.close();
}

void block_pop(ThreadSafeQueue<int> *q) {
	std::ofstream os;
	os.open("wait_and_pop_data");
	for (int i = 0; i < 1000; ++i) {
		auto p = q->wait_and_pop().get();
		if (p)
			os << *p << std::endl;
	}
	os.close();
}

int main()
{
	ThreadSafeQueue<int> q;	
	auto i = std::async(std::launch::async, 
		[](ThreadSafeQueue<int> *q){ push(q); }, &q);
	auto j = std::async(std::launch::async, 
		[](ThreadSafeQueue<int> *q){ try_pop(q); }, &q);
	auto k = std::async(std::launch::async, 
		[](ThreadSafeQueue<int> *q){ block_pop(q); }, &q);
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	i.get();
	j.get();
	k.get();
	return 0;
}
