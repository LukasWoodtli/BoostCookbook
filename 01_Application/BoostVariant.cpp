#include <boost/variant.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

void example1() {
	typedef boost::variant<int, const char*, std::string> my_var_t;

	std::vector<my_var_t> some_values;
	some_values.push_back(10);
	some_values.push_back("Hello there!");
	some_values.push_back(std::string("Wow!"));

	std::string& s = boost::get<std::string>(some_values.back());

	s += " That is great!\n";

	std::cout << s;
}

void example2() {
	// no empty state in Boost.Variant
	
	typedef boost::variant<boost::blank, int, std::string, const char*> my_var_t;
	
	// Default ctor will construct an instance of boost::blank
	my_var_t var;
	
	// The `empty()` method returns always 'false'
	assert(var.empty() == false);

	// the `which()? method returns the index of a type currently held by the variant
	assert(var.which() == 0); // empty

	var = "Hello";
	assert(var.which() != 0);
	std::cout << var.which() << "\n";
}

void example3() {
	boost::variant<int, std::string> variable(0);

	// this throws a `boost::bad_get` if `variable` is not an int
	int s1 = boost::get<int>(variable);
	assert(s1 == 0);

	// this returns `NULL` if `variable` is not an int
	int *s2 = boost::get<int>(&variable);
	assert(*s2 == 0);
}

int main() {
	example1();
	example2();
	example3();
	return 0;
}

