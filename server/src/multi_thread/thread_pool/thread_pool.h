#ifndef THREAD_POOL_H
#define THREAD_POOL_H 1

#include <vector>
#include <thread>
#include <utility>
#include <future>

#include "thread_safe_queue.h"

// Func is a callable, Args... are argument parameters
template <typename Func, typename... Args>
class ThreadPool {
public:
	
	typedef typename std::invoke_result<Func, Args...>::type result_type;
	
	// default ctor
	ThreadPool();

	// finish the waiting by stop resquest and release resource
	~ThreadPool() { finish(); }

	// submit the function just like a jthread 
	std::future<result_type> submit(Func &&, Args&&...);

	// stop the waiting works by stop request
	void finish();

private:

	// jobs to do by theads enable interrupt by stop token only for impl
	void work(std::stop_token st);

	// done flag
	bool done_;

	// task queue thread safe 
	ThreadSafeQueue<std::packaged_task<result_type()>> task_queue_;

	// container to hold jthreads auto join with dtors
	std::vector<std::jthread> threads_;
};

#include "thread_pool.tcc"

#endif // THREAD_POOL_H
