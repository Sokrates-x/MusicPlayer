#ifndef CONNECT_H
#define CONNECT_H 1

#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>

class Connect {
public:

	Connect(int fd, const sockaddr_in &addr) : socket_fd_(fd),
		target_addr_(addr) {}

	// disallow copy
	Connect(const Connect &) = delete;
	Connect &operator=(const Connect &) = delete;
	// move is okay
	Connect(Connect &&) = default;		
	Connect &operator=(Connect &&) = default;	

	virtual ~Connect() {}

	// this will use template method or strategy design partten
	// stop token can be used to cancle jobs whenever server need reboot
	void operator()(){
		doSth();
	}

protected:

	virtual void doSth();
	
private:
	int socket_fd_;
	sockaddr_in target_addr_;			
};

#endif // CONNECT_H
