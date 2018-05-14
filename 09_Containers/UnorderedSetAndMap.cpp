#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <chrono>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/lexical_cast.hpp>



void example() {
	boost::unordered_set<std::string> strings;

	strings.insert("This");
	strings.insert("is");
	strings.insert("an");
	strings.insert("example");

	assert(strings.find("is") != strings.cend());
}

template <class T>
void output_example() {
	T strings;

	strings.insert("CZ");
	strings.insert("CD");
	strings.insert("A");
	strings.insert("B");

	std::cout << '\n';
	std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << '\n';
}


template <class T>
std::size_t test_default() {
	const std::size_t ii_max = 20000;
	const std::string s("Test string");

	T map;

	std::cout << "Insert data" << '\n';
	auto start = std::chrono::system_clock::now();
	
	for (std::size_t ii = 0; ii < ii_max; ++ ii) {
		map[s + boost::lexical_cast<std::string>(ii)] = ii;
	}

	auto end = std::chrono::system_clock::now();
	auto elapsed = end - start;
	std::cout << elapsed.count() << '\n';

	
	// inserting once more
	std::cout << "Insert data once more" << '\n';
	start = std::chrono::system_clock::now();
	
	for (std::size_t ii = 0; ii < ii_max; ++ ii) {
		map[s + boost::lexical_cast<std::string>(ii)] = ii;
	}
	end = std::chrono::system_clock::now();
	elapsed = end - start;
	std::cout << elapsed.count() << '\n';

	return map.size();
}


// custom types in unordered container
struct my_type {
	int val1_;
	std::string val2_;
};

inline bool operator==(const my_type& v1, const my_type& v2) {
	return v1.val1_ == v2.val1_ && v1.val2_ == v2.val2_;
}

// for boost
std::size_t hash_value(const my_type& v) {
	std::size_t ret = 0u;

	// hash_combine not available in std C++11
	boost::hash_combine(ret, v.val1_);
	boost::hash_combine(ret, v.val2_);
	return ret;
}

// for C++11
namespace std {
template <> struct hash<my_type> {
		std::size_t operator()(my_type const& t) const noexcept
    {
			// no hash_combine function available
			std::size_t h1 = std::hash<int>{}(t.val1_);
			std::size_t h2 = std::hash<std::string>{}(t.val2_);
			return h1 ^ (h2 << 1);
		}
};
}

int main() {
	example();

	output_example<std::set<std::string>>();
	output_example<boost::unordered_set<std::string>>();
	output_example<std::unordered_set<std::string>>();

	test_default<std::map<std::string, std::size_t>>();
	test_default<boost::unordered_map<std::string, std::size_t>>();
	test_default<std::unordered_map<std::string, std::size_t>>();

	boost::unordered_set<my_type> my_set;
	my_set.insert(my_type{1, "a"});

	std::unordered_set<my_type> my_set_std;
	my_set_std.insert(my_type{2, "b"});
}
