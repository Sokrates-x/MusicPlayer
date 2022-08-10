/**
 * Description: A thread Safe Queue for movable or copyable elements. Push
 * Blocked Pop & Unblocked Pop are the only interface. And the Blocked Pop
 * is interrptable by pass an associate std::stop_token.
 */

#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE 1

#include <mutex>
#include <memory>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {

	// single list to impl the queue with dummy tail
	// CAN NOT pop from tail
	// use auto ptrs for resouce manage
	struct node {
		std::shared_ptr<T> data_;
		std::unique_ptr<node> next_;
	};

public:

	// default ctor
	ThreadSafeQueue() : head_(new node), tail_(head_.get()) {}

	// disallow copy
	ThreadSafeQueue(const ThreadSafeQueue &) = delete;
	ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

	// disallow move for same reason
	ThreadSafeQueue(ThreadSafeQueue &&) = delete;
	ThreadSafeQueue &operator=(ThreadSafeQueue &&) = delete;

	// default dtor because resouce release through auto ptrs..
	~ThreadSafeQueue() {}

	// interuptable wait and pop 
	// you can interrupt it through the stop_token but i do not known
	// whether the stop request's notify_all has race condition with push's
	// notify_one
	// use the try pop if possible
	std::shared_ptr<T> wait_and_pop(std::stop_token st);

	// unblocked  pop return immediatelly as if the lock if not accessiable
	std::shared_ptr<T> try_pop();

	// push back for move only objects & rvalue
	void push(T &&val);

	// push back overloads for copyable objects
	void push(const T &val);

private:

	// mutex for head & tail
	std::mutex head_mutex_;
	std::mutex tail_mutex_;
	//std::mutex cv_any_mutex_;
	
	// condtion variable any for push's notify one & stop request
	std::condition_variable_any cv_any_;

	// head & dummy tail for list
	std::unique_ptr<node> head_;
	node *tail_;
};

#include "thread_safe_queue.tcc"

#endif // THREAD_SAFE_QUEUE
