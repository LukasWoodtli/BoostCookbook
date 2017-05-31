#include <boost/icl/interval_set.hpp>

#include <iostream>

int main(void) {
	using namespace boost::icl;
	using IntervalSet = interval_set<int>;
	using Interval = interval<int>;
	
	IntervalSet a;
	a.insert(3);
	a.insert(7);
	
	Interval::type i(1, 9);
	IntervalSet b(i);
	
	auto c = b - a;
	
	for (auto i: c) {
		std::cout << i << "\n";
		std::cout << first(i) << "\n";
		std::cout << last(i) << "\n";
	}
}

