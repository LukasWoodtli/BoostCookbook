
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/numeric.hpp>

#include <list>

#include <iostream>


int main()
{
	std::list<int> a = {1,2,3,4};
	std::list<int> b;// = {5,6,7,8};
	auto iter = std::inserter(b, b.begin());
	boost::transform(a, iter, [](const int& i){return i + 1;});

	for (const int& j : b)
		std::cout << j << std::endl;

	return 0;
}
