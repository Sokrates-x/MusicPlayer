#include <future>
#include <memory>
#include <iostream>

void f() {	
	std::cout << "hello concurrency" << std::endl;
}

int main(int, char **)
{
	std::packaged_task<void ()> task(std::move(f));
	auto fut = task.get_future();
	auto p 
		= std::make_shared<std::packaged_task<void ()>>(std::move(task));

	p->operator()();
	return 0;
}
