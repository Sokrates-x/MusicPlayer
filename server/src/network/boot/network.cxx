#include "network.h"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <exception>
#include <iostream>

bool Network::flag_ = false; 

Network::Network() {
	// creat 
	socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd_ < 0)
		throw std::runtime_error("Creat Socket Failed!");

	// addr
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(19931);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// bind
	int n = bind(socket_fd_, reinterpret_cast<sockaddr *>(&addr), 
		sizeof(sockaddr_in));
	if (n != 0)
		throw std::runtime_error("Bind Failed.");
	
	// listen
	n = listen(socket_fd_, 10);
	if (n != 0)
		throw std::runtime_error("Listen Failed.");
}

Network::~Network() {
	close(socket_fd_);
}

std::shared_ptr<Network> Network::network_start() {
	if (flag_)
		throw std::runtime_error("Network Already Started.");
	std::shared_ptr<Network> ptr(new Network);
	flag_ = true;
	return ptr;
}
