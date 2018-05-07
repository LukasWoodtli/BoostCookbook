#include <string>
#include <iostream>
#include <algorithm>

#include <cstdlib>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/case_conv.hpp>



#define ASSERT(a) do {if(!(a)) { std::cerr << "Assertion error: " << __FILE__ << ":" << __LINE__ << "\n"; std::exit(EXIT_FAILURE); } } while(0)


namespace {
std::string str1 = "Thanks for reading me!";
std::string str2 = "Thanks for reading ME!";
}

int main() {

	ASSERT(boost::iequals(str1, str2));


	ASSERT(str1.size() == str2.size() &&
		std::equal(str1.begin(),
			         str1.end(),
							 str2.begin(),
							 boost::is_iequal()));


	// lowercase copy of strings
	const std::string str1_low = boost::to_lower_copy(str1);
	const std::string str2_low = boost::to_lower_copy(str2);
	ASSERT(str1_low == str2_low);


	// uppercase copy of strings
	const std::string str1_up = boost::to_upper_copy(str1);
	const std::string str2_up = boost::to_upper_copy(str2);
	ASSERT(str1_up == str2_up);


	// original strings to lowercase
	boost::to_lower(str1);
	boost::to_lower(str2);
	ASSERT(str1 == str2);


	// A locale can be provided otherwise it's default constructed.
	// It's faster to create a locale once and use it in all functions.
	const auto LOCALE = std::locale::classic(); // on some platforms faster than std::locale()
	ASSERT(boost::iequals(str1, str2, LOCALE));

}
