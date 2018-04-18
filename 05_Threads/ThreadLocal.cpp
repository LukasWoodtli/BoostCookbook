#include <iostream>
#include <atomic>
#include <thread>
#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/tss.hpp>


class connection : boost::noncopyable {
public:
	connection() { ++connection_num_; }
	void open() {std::cout << "open\n";}

	void send_result(int result) {std::cout << "result: " << result << "\n" << "connections " << connection_num_ << "\n\n";}
	
	static std::atomic<int> connection_num_;
};

std::atomic<int> connection::connection_num_ = 0;


///////////////////////////
// Boost //////////////////
///////////////////////////
boost::thread_specific_ptr<connection> connection_ptr;

connection& get_connection() {
	connection* p = connection_ptr.get();

	if (!p) {
		connection_ptr.reset(new connection);
		p = connection_ptr.get();
		p->open();
	}

	return *p;
}

void task() {
	int result;
	// computations go here
	result = 43;
	
	// sending result
	get_connection().send_result(result);
}


///////////////////////////
// C++11 //////////////////
///////////////////////////
thread_local std::shared_ptr<connection> connection_ptr_std;

connection& get_connection_std() {
	connection* p = connection_ptr_std.get();

	if (!p) {
		connection_ptr_std.reset(new connection);
		p = connection_ptr_std.get();
		p->open();
	}

	return *p;
}

void task_std() {
	int result;
	// computations go here
	result = 43;
	
	// sending result
	get_connection_std().send_result(result);
}




int main() {
		// Boost //////////////////

	boost::thread t1(&task);
	boost::thread t2(&task);
	boost::thread t3(&task);

	t1.join();
	t2.join();
	t3.join();


	// C++11 //////////////////
	std::thread t4(&task_std);
	std::thread t5(&task_std);
	std::thread t6(&task_std);

	t4.join();
	t5.join();
	t6.join();

}
