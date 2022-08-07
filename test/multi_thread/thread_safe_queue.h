#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE 1

#include <mutex>
#include <memory>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {

	struct node {
		std::shared_ptr<T> data_;
		std::unique_ptr<node> next_;
	};

public:

	ThreadSafeQueue() : head_(new node), tail_(head_.get()) {}
	ThreadSafeQueue(const ThreadSafeQueue &) = delete;
	ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

	// interuptable wait and pop 
	std::shared_ptr<T> wait_and_pop(std::stop_token st) {
		std::unique_lock<std::mutex> head_lock(head_mutex_);
		//std::unique_lock<std::mutex> tail_lock(tail_mutex_);
		cv_any_.wait(head_lock, st, [this](){ 
			return this->head_.get() != this->tail_; });
		if (st.stop_requested()) {
			throw std::runtime_error("Pop Interrupted.");
		}
		//tail_lock.unlock();
		std::unique_ptr<node> old_head = std::move(head_);
		head_ = std::move(old_head->next_);
		return old_head->data_;
	}

	std::shared_ptr<T> try_pop() {
		std::lock_guard<std::mutex> head_lock(head_mutex_);
		//std::unique_lock<std::mutex> tail_lock(tail_mutex_);
		if (head_.get() == tail_)
			return std::shared_ptr<T>();
		//tail_lock.unlock();
		std::unique_ptr<node> old_head = std::move(head_);
		head_ = std::move(old_head->next_);
		return old_head->data_;
	}

	void push(T &&val) {
		std::shared_ptr<T> new_data(std::make_shared<T>(std::move(val)));
		std::unique_ptr<node> p(new node);
		node * const new_tail = p.get();
		std::lock_guard<std::mutex> tail_lock(tail_mutex_);
		tail_->data_ = new_data;
		tail_->next_ = std::move(p);
		tail_ = new_tail;
		//std::lock_guard<std::mutex> cv_any_lock(cv_any_mutex_);
		cv_any_.notify_one();
	}

	void push(const T &val) {
		std::shared_ptr<T> new_data(std::make_shared<T>(val));
		std::unique_ptr<node> p(new node);
		node * const new_tail = p.get();
		std::lock_guard<std::mutex> tail_lock(tail_mutex_);
		tail_->data_ = new_data;
		tail_->next_ = std::move(p);
		tail_ = new_tail;
		//std::lock_guard<std::mutex> cv_any_lock(cv_any_mutex_);
		cv_any_.notify_one();
	}

private:

	// mutex
	std::mutex head_mutex_;
	std::mutex tail_mutex_;
	//std::mutex cv_any_mutex_;
	
	// condtion variable
	std::condition_variable_any cv_any_;

	// nodes for list
	std::unique_ptr<node> head_;
	node *tail_;
};

#endif // THREAD_SAFE_QUEUE
