#ifndef THREAD_POOL_H
#define THREAD_POOL_H 1

#include <vector>
#include <thread>
#include <utility>
#include <future>

#include "thread_safe_queue.h"

template <typename Func, typename... Args>
class ThreadPool {
public:
	typedef typename std::invoke_result<Func, Args...>::type result_type;
	
	ThreadPool() : done_(false) {
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

	~ThreadPool() { 
		finish();
	}

	std::future<result_type> submit(Func f, Args&&... args) {
		std::packaged_task<result_type()> 
			task([&] { return f(std::forward<Args>(args)...); });
		auto res = task.get_future();
		task_queue_.push(std::move(task));
		return res;
	}

	void finish() {
		for (auto &ths : threads_)
			ths.request_stop();
		done_ = true;
	}

private:
	void work(std::stop_token st) {
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

	bool done_;
	ThreadSafeQueue<std::packaged_task<result_type()>> task_queue_;
	std::vector<std::jthread> threads_;
};

#endif // THREAD_POOL_H
