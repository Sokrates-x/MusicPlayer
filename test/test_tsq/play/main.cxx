#include <thread>

class s {
	thread_local std::stop_token stoken_;
};
int main()
{
	std::stop_token stoken_;
}
