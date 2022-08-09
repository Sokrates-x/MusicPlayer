#ifndef NETWORK_H
#define NETWORK_H 1

#include <memory>

class Network;

class Network {
public:

	~Network();
	Network(const Network &) = delete;
	Network &operator=(const Network &) = delete;

	static std::shared_ptr<Network> network_start();

	int get_socket() const { return socket_fd_; }

private:

	Network();
	int socket_fd_;
	static bool flag_;
};

#endif //NETWORK_H
