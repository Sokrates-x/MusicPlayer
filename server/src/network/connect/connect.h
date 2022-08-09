#ifndef CONNECT_H
#define CONNECT_H 1

class Connect {
public:
	Connect() = delete;
	explicit Connect(int fd) : socket_fd_(fd) {}

	void operator()();
	
private:
	int socket_fd_;
	sock
};

#endif // CONNECT_H
