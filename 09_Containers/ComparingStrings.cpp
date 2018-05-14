#include <iostream>
#include <string>
#include <functional>

#include <boost/functional/hash.hpp>


template <class T>
std::size_t test_default() {
	const std::size_t ii_max = 20000;
	const std::string s("Long long string tha will be used "
		"in tests to compare speed of equality comparisons.");

	// data to be used in comparisons
	const T data[] = {
		T(s),
		T(s + s),
		T(s + ". Woooohoooo"),
		T(std::string(""))
	};

	const std::size_t data_dimensions = sizeof(data) / sizeof(*data);
	std::size_t matches = 0u;
	for (std::size_t ii = 0; ii < ii_max; ++ii) {
		for (std::size_t i = 0; i < data_dimensions; ++i) {
			for (std::size_t j = 0; j < data_dimensions; ++j) {
				if (data[i] == data[j]) {
					++matches;
				}
			}
		}
	}

	return matches;
}


struct string_hash_fast {
	typedef std::size_t comp_type;

	const comp_type comparison_;
	const std::string str_;

	explicit string_hash_fast(const std::string& s)
		: comparison_(std::hash<std::string>()(s)), str_(s) // for boost use: boost::hash<..>
		{}
};

inline bool operator== (const string_hash_fast& s1, const string_hash_fast& s2) {
	return s1.comparison_ == s2.comparison_ &&
		s1.str_ == s2.str_;
}

inline bool operator!= (const string_hash_fast& s1, const string_hash_fast& s2) {
	return not(s1 == s2);
}


int main() {
	bool success = (test_default<string_hash_fast>() == test_default<std::string>());
	
	if (success)
		return 0;

	return -1;
}
