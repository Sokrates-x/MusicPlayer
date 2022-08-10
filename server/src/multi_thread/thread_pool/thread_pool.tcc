#include "thread_pool.h"

template <typename Func, typename... Args>
ThreadPool<Func, Args...>::ThreadPool() : done_(false) {
	auto th_n = std::thread::hardware_concurrency();
	try {
		for (int i = 0; i < th_n; ++i) {
			threads_.push_back(std::jthread(
				[this] (std::stop_token st) { this->work(st); }));
		}
	} catch (...) {
		done_ = true;
		throw;
	}
}

template <typename Func, typename... Args>
void ThreadPool<Func, Args...>::finish() {
	for (auto &ths : threads_)
		ths.request_stop();
	done_ = true;
}

template <typename Func, typename... Args>
void ThreadPool<Func, Args...>::work(std::stop_token st) {
	while (!done_) {
		try {
			// enable interrupt when wait for a pop
			// I wonder if the stop request in contention with the
			// push's notify_one
			auto p = task_queue_.wait_and_pop(st);
			p->operator()();
		} catch (...) {
			// just skip a stop request & turn to 
		}
	}
}

template <typename Func, typename... Args>
std::future<typename ThreadPool<Func, Args...>::result_type> 
	ThreadPool<Func, Args...>::submit(Func&& f, Args&&... args) {
	std::packaged_task<result_type()> task([&] { 
		return std::forward<Func>(f)(std::forward<Args>(args)...); });
	auto res = task.get_future();
	task_queue_.push(std::move(task));
	return res;
}
