#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

typedef boost::bimap<std::string, boost::bimaps::multiset_of<std::size_t>> name_id_type;

int main() {
	
	name_id_type name_id;
	name_id.insert(name_id_type::value_type("A.B", 1));
	name_id.insert(name_id_type::value_type("C.D", 2));
	name_id.insert(name_id_type::value_type("E.F", 3));
	name_id.insert(name_id_type::value_type("G.H", 4));


	std::cout << "Left:\n";
	typedef name_id_type::left_const_iterator left_const_iterator;
	for (left_const_iterator it = name_id.left.begin(), iend = name_id.left.end(); it != iend; ++it) {
		std::cout << it->first << " <=> " << it->second << '\n';
	}

	std::cout << "\nRight:\n";
	typedef name_id_type::right_const_iterator right_const_iterator;
	for (right_const_iterator it = name_id.right.begin(), iend = name_id.right.end(); it != iend; ++it) {
		std::cout << it->first << " <=> " << it->second << '\n';
	}

	// search
	auto found = name_id.find(name_id_type::value_type("A.B", 3)) != name_id.end();
	assert(found);
}
