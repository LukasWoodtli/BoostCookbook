#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/atomic.hpp>

/* All the processes that are using shared memory must run on the same host or on 
 * a symmetric multiprocessing (SMP) cluster. */

typedef boost::atomic<int> atomic_t;

#if (BOOST_ATOMIC_INT_LOCK_FREE != 2)
# error "This code requires lock-free boost::atomic<int>"
#endif


int main() {
	boost::interprocess::managed_shared_memory segment(boost::interprocess::open_or_create, "shm-cache", 1024);
	atomic_t& atomic = *segment.find_or_construct<atomic_t>("shm-counter")(0);

	std::cout << "I have index " << ++atomic << "\npress any key... ";
	std::cin.get();

	int snapshot = --atomic;
	if (!snapshot) {
		segment.destroy<atomic_t>("shm-counter");
		boost::interprocess::shared_memory_object::remove("shm-cache");
	}
}
