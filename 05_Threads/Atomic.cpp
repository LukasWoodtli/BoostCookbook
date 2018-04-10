#include <cassert>
#include <cstddef>
#include <iostream>

#include <atomic>
#include <thread>

#include <boost/thread/thread.hpp>
#include <boost/atomic.hpp>

// Boost
boost::atomic<int> shared_i(0);

void do_inc() {
	for (std::size_t i = 0; i < 30000; ++i) {
		const int i_snapshot = ++shared_i;

		// do some work here
		(void)i_snapshot;
	}
}

void do_dec() {
	for (std::size_t i = 0; i < 30000; ++i) {
		const int i_snapshot = --shared_i;

		// do some work here
		(void)i_snapshot;
	}
}


// C++11
std::atomic<int> shared_i_std(0);

void do_inc_std() {
	for (std::size_t i = 0; i < 30000; ++i) {
		const int i_snapshot = ++shared_i_std;

		// do some work here
		(void)i_snapshot;
	}
}

void do_dec_std() {
	for (std::size_t i = 0; i < 30000; ++i) {
		const int i_snapshot = --shared_i_std;

		// do some work here
		(void)i_snapshot;
	}
}


int main() {
	// boost
	boost::thread t1(&do_inc);
	boost::thread t2(&do_dec);

	t1.join();
	t2.join();

	assert(shared_i == 0);
	std::cout << "boost: shared_i == " << shared_i << "\n";
	
	// C++11
	std::thread t3(&do_inc_std);
	std::thread t4(&do_dec_std);

	t3.join();
	t4.join();

	assert(shared_i_std == 0);
	std::cout << "C++11: shared_i == " << shared_i_std << "\n";
}
