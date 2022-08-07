#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>

void f(std::stop_token st) {
	std::mutex mt;
	std::unique_lock<std::mutex> lk(mt);
	std::condition_variable_any().wait(lk, st, [] {return false; });
	if (st.stop_requested())
		std::cout << "Stoped." << std::endl;
}

int main() {
	std::jthread j([](std::stop_token st) {f(st);});	
	j.request_stop();
	return 0;
}
