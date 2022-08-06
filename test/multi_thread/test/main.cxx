#include <iostream>

int f(int) {
	return 0;
}

void g(std::invoke_result<int(int), int>::type f) {
	f = 1;
}

int main()
{
}
