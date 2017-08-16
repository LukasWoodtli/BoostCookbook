#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <vector>
#include <iostream>


void wierd_appender(std::string& to, const std::string& from) {
	to += from;
}


int main() {
	boost::array<int, 12> values = {{1, 2, 3, 4, 5, 6, 7, 100, 99, 98, 97, 96}};

	std::size_t count0 = std::count_if(values.begin(), values.end(),
			std::bind1st(std::less<int>(), 5));

	std::size_t count1 = std::count_if(values.begin(), values.end(),
			boost::bind(std::less<int>(), 5, _1));
	// C++11 style
	std::size_t count2 = std::count_if(values.begin(), values.end(),
			std::bind(std::less<int>(), 5, std::placeholders::_1));

	std::cout << "cout0 " << count0 << "\n";
	std::cout << "cout1 " << count1 << "\n";
	std::cout << "cout2 " << count2 << "\n\n";

	assert(count0 == count1);
	assert(count0 == count2);


	
	boost::array<std::string, 3> str_values = {{"We ", "are", " the champions!"}};

	count0 = std::count_if(str_values.begin(), str_values.end(),
			std::mem_fun_ref(&std::string::empty));
	count1 = std::count_if(str_values.begin(), str_values.end(),
			boost::bind(&std::string::empty, _1));
	// C++11 style
	count2 = std::count_if(str_values.begin(), str_values.end(),
			std::mem_fn(&std::string::empty));

	
	std::cout << "cout0 " << count0 << "\n";
	std::cout << "cout1 " << count1 << "\n";
	std::cout << "cout2 " << count2 << "\n\n";

	assert(count0 == count1);
	assert(count0 == count2);


	count1 = std::count_if(str_values.begin(), str_values.end(),
			boost::bind(std::less<std::size_t>(),
				boost::bind(&std::string::size, _1), 5));
	// C++11
	count2 = std::count_if(str_values.begin(), str_values.end(),
			std::bind(std::less<std::size_t>(),
				std::bind(&std::string::size, std::placeholders::_1), 5));
	
	std::cout << "cout1 " << count1 << "\n";
	std::cout << "cout2 " << count2 << "\n\n";
	
	assert(2 == count1);
	assert(2 == count2);



	std::string s("Expensive copy ctor of std::string will be called");
	count0 = std::count_if(str_values.begin(), str_values.end(), std::bind2nd(std::less<std::string>(), s));
	count1 = std::count_if(str_values.begin(), str_values.end(), boost::bind(std::less<std::string>(), _1, s));
	// C++11
	count2 = std::count_if(str_values.begin(), str_values.end(), std::bind(std::less<std::string>(), std::placeholders::_1, s));

	std::cout << "cout1 " << count1 << "\n";
	std::cout << "cout2 " << count2 << "\n\n";
	
	assert(count0 == count1);
	assert(count0 == count2);



	s = "Expensive copy ctor of std::string will NOT be called anymore";
	count0 = std::count_if(str_values.begin(), str_values.end(), std::bind2nd(std::less<std::string>(), boost::cref(s)));
	count1 = std::count_if(str_values.begin(), str_values.end(), boost::bind(std::less<std::string>(), _1, boost::cref(s)));
	// C++11
	count2 = std::count_if(str_values.begin(), str_values.end(), std::bind(std::less<std::string>(), std::placeholders::_1, std::cref(s)));

	std::cout << "cout1 " << count1 << "\n";
	std::cout << "cout2 " << count2 << "\n\n";
	
	assert(count0 == count1);
	assert(count0 == count2);



	std::string result;
	std::for_each(str_values.cbegin(), str_values.cend(), boost::bind(&wierd_appender, boost::ref(result), _1));
	assert(result == "We are the champions!");

	// C++11
	result = "";
	std::for_each(str_values.cbegin(), str_values.cend(), std::bind(&wierd_appender, std::ref(result), std::placeholders::_1));
	assert(result == "We are the champions!");



	return 0;
}

