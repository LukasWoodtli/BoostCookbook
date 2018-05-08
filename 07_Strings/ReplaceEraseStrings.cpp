#include <string>
#include <iostream>

#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/replace.hpp>

const std::string str = "Hello, hello, dear Reader.";

namespace ba = boost::algorithm;

int main() {
	std::cout << "\n erase_all_copy   : " << ba::erase_all_copy(str, ",");
	std::cout << "\n erase_first_copy : " << ba::erase_first_copy(str, ",");
	std::cout << "\n erase_last_copy  : " << ba::erase_last_copy(str, ",");
	std::cout << "\n ierase_all_copy  : " << ba::ierase_all_copy(str, "hello");
	std::cout << "\n ierase_nth_copy  : " << ba::ierase_nth_copy(str, ",", 1);
	std::cout << "\n";

	std::cout << "\n replace_all_copy   : " << ba::replace_all_copy(str, ",", "!");
	std::cout << "\n replace_first_copy : " << ba::replace_first_copy(str, ",", "!");
	std::cout << "\n replace_head_copy  : " << ba::replace_head_copy(str, 6, "Whaaaaaa!");
	std::cout << "\n";

	
}