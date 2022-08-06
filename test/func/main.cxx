#include <functional>
#include <functional>

void f (int, int) {

}

int main(int, char **)
{
	std::function<void (int, int)> F(f);
	F(1,2);
	return 0;
}
