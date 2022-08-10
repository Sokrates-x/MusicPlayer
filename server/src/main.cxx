#include <vector>
#include "network.h"
#include "thread_pool.h"
#include "connect.h"

int main() {

	auto nw = Network::network_start();
	int sid = nw->get_socket();
	
	// thread
	ThreadPool<Connect &&> pool;

	// futrues
	std::vector<std::future<void>> futures;

	while (true) {
		sockaddr_in addr;
		socklen_t len;

		int new_sid = accept(sid, reinterpret_cast<sockaddr *>(&addr), 
			&len);

		Connect con(new_sid, addr);
		futures.push_back(pool.submit(std::move(con)));
	}

	for (auto &m : futures) {
		m.get();
	}

	pool.finish();

	return 0;
}
