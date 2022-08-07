#include <thread>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <iostream>

void f(std::stop_token st) {
	std::mutex mt;
	std::unique_lock<std::mutex> lk(mt);
	std::condition_variable_any().wait(lk, st, [] { return false; });
	if (st.stop_requested())
		throw std::runtime_error("F Interrupted");
}

int main(){
		std::cout << "run jthread" << std::endl;
		std::jthread j([] (std::stop_token st) { 
		try {
			f(st); 
			std::cout << "continue" << std::endl;
		} catch (...) {
			std::cout << "interrupted" << std::endl;
		}
		std::cout << "interrupt jthread" << std::endl;
		});

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		std::jthread k(f);

	return 0;
}
