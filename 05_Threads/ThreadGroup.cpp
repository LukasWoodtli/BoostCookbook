#include <boost/thread.hpp>


static void worker() {
	std::cout << "Start thread\n";
	for (int i = 0; i < 300; ++i) {
		std::cout << i << "\n";
	}
		std::cout << "\n\n";
}


int main() {
	boost::thread_group threads;

	for (int i = 0; i < 5; ++i) {
		threads.create_thread(&worker);
	}

	threads.join_all();
}
