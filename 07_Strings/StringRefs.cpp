#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>

#include <boost/utility/string_ref.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

boost::string_ref between_str(const boost::string_ref& input, char starts, char ends) {

	boost::string_ref::const_iterator pos_beg = std::find(input.cbegin(), input.cend(), starts);

	if (pos_beg == input.cend()) {
		return boost::string_ref();
	}


	++pos_beg;
	boost::string_ref::const_iterator pos_end = std::find(input.cbegin(), input.cend(), ends);

	if (pos_end == input.cend()) {
		return boost::string_ref(pos_beg, input.end() - pos_beg);
	}
	
	return boost::string_ref(pos_beg, pos_end - pos_beg);
	
}

void string_ref_alorithms_examples() {
	boost::string_ref r("O_O");

	// finding symbol
	std::find(r.cbegin(), r.cend(), '_');

	// only *_copy functions work because boost::string_ref doesn't own the data of the string
	boost::to_lower_copy(std::ostream_iterator<char>(std::cout), r);
	std::cout << '\n';

	std::cout << r << '\n';

	boost::replace_all_copy(std::ostream_iterator<char>(std::cout), r, "O", "^");
	
}

int main() {
	std::cout << between_str("Getting expression (between brackes)", '(', ')');

	std::cout << "\n\n";

	string_ref_alorithms_examples();

	std::cout << '\n';
}
