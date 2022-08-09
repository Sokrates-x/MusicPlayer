#include "network.h"
#include <iostream>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <thread>

int main() {
	auto nw = Network::network_start();
	int sid = nw->get_socket();
	
	
	// thread
	while (true)
		std::thread

	sockaddr_in addr;
	socklen_t len;
	int new_sid = accept(sid, reinterpret_cast<sockaddr *>(&addr), &len);
	std::thread th(Connect(new_sid, addr.sin_family, addr.sin_port, 
		addr.sin_addr.s_addr)());
	th.atach()

	send(new_sid, "hello", 5, 0);

	return 0;	
}
