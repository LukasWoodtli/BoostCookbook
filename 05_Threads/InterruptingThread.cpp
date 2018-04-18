#include <iostream>
#include <boost/thread/thread.hpp>

#include <unistd.h>

void do_parse() {
	while (true) {
		boost::this_thread::interruption_point();
		// parse
		std::cout << "Parsing ...\n";
		usleep(500);
	}
}


int main() {
	boost::thread t1(&do_parse);

	sleep(1);
	t1.interrupt();

	t1.join();
}
