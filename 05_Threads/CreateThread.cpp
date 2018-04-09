#include <algorithm>
#include <fstream>
#include <iterator>
#include <functional>
#include <thread>

#include <boost/thread.hpp>


// long executing functions
void fill_file_with_data(char fill_char, std::size_t size, const char* filename) {
	std::ofstream ofs(filename);
	std::fill_n(std::ostreambuf_iterator<char>(ofs), size, fill_char);
}




int main() {
	// boost
	boost::thread t1(boost::bind(&fill_file_with_data, 0, 8 * 1024 *1024, "save_file_boost.txt"));
	
	// The thread must be joined or detached before its destructor is called. Otherwise, your program will terminate!
	t1.join();


	// C++11
	std::thread t2(std::bind(&fill_file_with_data, 0xfe, 8 * 1024 * 1024, "save_file_cpp11.txt"));
	
	t2.join();
}
