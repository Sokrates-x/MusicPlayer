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
				threads_.push_back(std::jthread(&ThreadPool::work, this));
			}
		} catch (...) {
			done_ = true;
			throw;
		}
	}

	~ThreadPool() { 
		done_ = true;
	}

	std::future<result_type> submit(Func f, Args&&... args) {
		std::packaged_task<result_type()> 
			task([&] { return f(std::forward<Args>(args)...); });
		auto res = task.get_future();
		task_queue_.push(std::move(task));
		return res;
	}

	void finish() {
		done_ = true;
	}

private:
	void work() {
		while (!done_) {
			auto p = task_queue_.wait_and_pop();
			p->operator()();
		}
	}

	bool done_;	
	ThreadSafeQueue<std::packaged_task<result_type()>> task_queue_;
	std::vector<std::jthread> threads_;
};

#endif // THREAD_POOL_H
