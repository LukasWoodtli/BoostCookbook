#include <vector>
#include <list>
#include <iostream>
#include <type_traits>

#include <boost/type_traits/integral_constant.hpp>

/////////////////////////////////////////////////////////////////////
/// Boost ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <class T>
struct is_stdvector : boost::false_type {};

template <class T, class Allocator>
struct is_stdvector<std::vector<T, Allocator>> : boost::true_type {};

static_assert(is_stdvector<std::vector<int>>::value == true, "");
static_assert(is_stdvector<std::list<int>>::value == false, "");
static_assert(is_stdvector<int>::value == false, "");



/////////////////////////////////////////////////////////////////////
/// C++11 ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <class T>
struct is_stdvector_std : std::false_type {};

template <class T, class Allocator>
struct is_stdvector_std<std::vector<T, Allocator>> : std::true_type {};

static_assert(is_stdvector_std<std::vector<int>>::value == true, "");
static_assert(is_stdvector_std<std::list<int>>::value == false, "");
static_assert(is_stdvector_std<int>::value == false, "");


int main() {

	std::cout << std::boolalpha;
/////////////////////////////////////////////////////////////////////
/// Boost ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	std::cout << "Boost:\n";
	std::cout << "std::vector<int> is std:vector: " << is_stdvector<std::vector<int>>::value << "\n";
	std::cout << "std::list<int> is std:vector: " << is_stdvector<std::list<int>>::value << "\n";
	std::cout << "int is std:vector: " << is_stdvector<int>::value << "\n";

/////////////////////////////////////////////////////////////////////
/// C++11 ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	std::cout << "\nC++11:\n";
	std::cout << "std::vector<int> is std:vector: " << is_stdvector_std<std::vector<int>>::value << "\n";
	std::cout << "std::list<int> is std:vector: " << is_stdvector_std<std::list<int>>::value << "\n";
	std::cout << "int is std:vector: " << is_stdvector_std<int>::value << "\n";

}
