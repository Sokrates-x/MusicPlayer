#ifndef THREAD_POOL_H
#define THREAD_POOL_H 1

#include <vector>
#include <thread>
#include <utility>

#include "thread_safe_queue.h"

class ThreadPool {
public:

	ThreadPool() : done_(false) {
		auto th_n = std::thread::hardware_concurrency();	
		try {
			for (int i = 0; i < th_n; ++i) {
				threads_.push_back(std::jthread(&work, this));
			}
		} catch (...) {
			done_ = true;
			throw;
		}
	}
	~ThreadPool() { done_ = true; }

	template<typename Func, typename... Args>
	std::future<typename std::result_of<Func(Args...)>::type>
		submit(Func f, Args&&... args) {
		std::packaged_task<typename std::result_of<Func(Args...)>::type> 
			task([&] { return f(std::forword<Args>(args)...); });
		auto res = task.get_future();
		task_queue_.push(std::move(task));
		return res;
	}

private:
	void work() {
		while (!done_) {
			auto p = task_queue_.wait_and_pop();
			p->operator()();
		}
	}

	ThreadSafeQueue<std::packaged_task<void()>> task_queue_;
	std::vector<std::jthread> threads_;
	bool done_;	
};

#endif // THREAD_POOL_H
