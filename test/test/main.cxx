#include "thread_safe_queue.h"
#include <future>
#include <iostream>

void f() {
	std::cout << "hello concurrcy." << std::endl;
}

class C {
public:
	C() {
		std::cout << "ctor" << std::endl;
	}
	C(const C &) {
		std::cout << "ctor" << std::endl;
	}
	~C() {
		std::cout << "dtor" << std::endl;
	}
};

int main(int, char **)
{
	ThreadSafeQueue<std::packaged_task<void ()>> q;
	q.push(std::packaged_task<void ()>(std::move(f)));
	q.try_pop()->operator()();
	
	ThreadSafeQueue<int> qq;
	qq.push(3);

	C c;	
	ThreadSafeQueue<C> qqq;
	qqq.push(c);
	return 0;
}
