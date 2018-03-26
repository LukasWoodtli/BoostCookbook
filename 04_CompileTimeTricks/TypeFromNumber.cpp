#include <iostream>

#include <boost/mpl/int.hpp>
#include <boost/type_traits.hpp>

namespace detail {
	// generic implementation
	template <class T, class Tag>
	T process_impl(const T& val, Tag /* ignore */) {
		std::cout << "Generic implementation\n";
		// ...
		return val;
	}

	// 1 byte optimized inplementation
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<1> /* ignore */) {
		std::cout << "1 byte optimized implementation\n";
		// ...
		return val;
	}

	// 4 byte optimized inplementation
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<4> /* ignore */) {
		std::cout << "4 byte optimized implementation\n";
		// ...
		return val;
	}

		// 8 byte optimized inplementation
	template <class T>
	T process_impl(const T& val, boost::mpl::int_<8> /* ignore */) {
		std::cout << "8 byte optimized implementation\n";
		// ...
		return val;
	}

}


template <class T>
T process(const T& val) {
	static_assert(boost::is_pod<T>::value, "Not POD!");
	return detail::process_impl(val, boost::mpl::int_<sizeof(T)>());
}

struct test_small {};
struct test_big { char data[100]; };
int main() {
	process((char)1);
	process(15);
	process(9999999999L);

	test_small t1;
	process(t1);

	test_big t2;
	process(t2);
}
