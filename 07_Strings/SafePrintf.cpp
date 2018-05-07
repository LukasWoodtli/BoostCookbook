#include <string>
#include <iostream>

#include <boost/format.hpp>


class i_hold_some_internals {
	int i;
	std::string s;
	char c;

public:
	i_hold_some_internals(int i, const std::string& s, char c)
		: i(i), s(s), c(c)
		{}

	// fmt parameter must contain the following:
	//  $1$ for outputting integer 'i'
	//  $2$ for outputting string 's'
	//  $3$ for outputting character 'c
	std::string to_string(const std::string& format_specifier) const {
		boost::format f(format_specifier);
		unsigned char flags = boost::io::all_error_bits;
		flags ^= boost::io::too_many_args_bit;
		f.exceptions(flags);
		return (f % i % s % c).str();
	}

};

int main() {
	i_hold_some_internals class_instance(100, "Reader", '!');
	
	std::cout << class_instance.to_string(
		"Hello, dear %2%! "
		"Did you read the book for %1% %% %3%\n");

	std::cout << class_instance.to_string(
		"%1% == %1% && %1%%% != %1%\n\n");

	std::cout << class_instance.to_string("%2%\n\n");

	try {
		class_instance.to_string("%1% %2% %3% %4% %5%\n");
		assert(false); return(-1);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

}
