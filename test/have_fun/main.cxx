#include <iostream>
#include <functional>
#include <utility>

int i = 100;

void f(int &i) {
	++i;
}

void g(int &&i) {
	++i;
}

template <typename Func, typename... Args>
typename std::result_of<Func(Args...)>::type call(Func f, Args&&... args) {
	auto g = [&] { return f(std::forward<Args>(args)...); };
	g();
}


int main(int, char **)
{
	f(i);
	std::cout << i << std::endl;
	call(f, i);	
	std::cout << i << std::endl;

	call(g, 100);
	std::cout << i << std::endl;
	return 0;
}
