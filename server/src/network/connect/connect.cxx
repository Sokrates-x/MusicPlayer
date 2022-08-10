#include "connect.h"

#include <iostream>

void Connect::doSth() {
	send(socket_fd_, "hello", 5, 0);
	std::cout << std::this_thread::get_id() << std::endl;
}
