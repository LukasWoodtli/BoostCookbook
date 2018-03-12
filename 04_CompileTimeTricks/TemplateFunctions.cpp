#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>

#include <type_traits>

#include <iostream>

/*** Boost *************************************************************************************/

// generic
template <class T, class Enable = void>
class data_processor {
public:
	double process(const T& v1, const T& v2, const T& v3) {
		std::cout << "Generic implementation\n";
		std::cout << v1 << ", " << v2 << ", " << v3 << "\n\n";
		return 0.0;
	}
};


// int optimized verion
template <class T>
class data_processor<T, typename boost::enable_if_c<boost::is_integral<T>::value>::type> {
public:
	typedef int fast_int_t;
	double process(fast_int_t v1, fast_int_t v2, fast_int_t v3) {
		std::cout << "Int optimized implementation\n";
		std::cout << v1 << ", " << v2 << ", " << v3 << "\n\n";
		return 1.0;
	}
};

// sse optimized version for floats
template<class T>
class data_processor<T, typename boost::enable_if_c<boost::is_float<T>::value>::type> {
public:
	double process(double v1, double v2, double v3) {
		std::cout << "Double (SSE) optimized implementation\n";
		std::cout << v1 << ", " << v2 << ", " << v3 << "\n\n";
		return 3.14;
	}
};



/*** C++11 **************************************************************************************/

// generic
template <class T, class Enable = void>
class data_processor_std {
public:
	double process(const T& v1, const T& v2, const T& v3) {
		std::cout << "Generic implementation\n";
		std::cout << v1 << ", " << v2 << ", " << v3 << "\n\n";
		return 0.0;
	}
};

// int optimized verion
template <class T>
class data_processor_std<T, typename std::enable_if<std::is_integral<T>::value>::type> {
public:
	typedef int fast_int_t;
	double process(fast_int_t v1, fast_int_t v2, fast_int_t v3) {
		std::cout << "Int optimized implementation\n";
		std::cout << v1 << ", " << v2 << ", " << v3 << "\n\n";
		return 1.0;
	}
};

// sse optimized version for floats
template<class T>
class data_processor_std<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
public:
	double process(double v1, double v2, double v3) {
		std::cout << "Double (SSE) optimized implementation\n";
		std::cout << v1 << ", " << v2 << ", " << v3 << "\n\n";
		return 3.14;
	}
};




/// Tests /////////////////////////////////////////////////////////////////////////////////

/*** Boost *************************************************************************************/
template <class T>
double example_func(T v1, T v2, T v3) {
	data_processor<T> proc;
	return proc.process(v1, v2, v3);
}

/*** C++11 **************************************************************************************/

template <class T>
double example_func_std(T v1, T v2, T v3) {
	data_processor_std<T> proc;
	return proc.process(v1, v2, v3);
}


int main() {

/*** Boost *************************************************************************************/

	std::cout << "Boost:\n\n";
	// int optimized version called
	example_func(1, 2, 3);
	short s = 0;
	example_func(s, s, s);

	// float optimized version is called
	example_func(1.0, 1.2, 3.0);
	example_func(1.0f, 1.2f, 3.0f);

	// generic function is called
	example_func("Hello", "Wold", "...");

/*** C++11 **************************************************************************************/

	std::cout << "\n\nC++11:\n\n";
	// int optimized version called
	example_func_std(1, 2, 3);
	short t = 0;
	example_func_std(t, t, t);

	// float optimized version is called
	example_func_std(1.0, 1.2, 3.0);
	example_func_std(1.0f, 1.2f, 3.0f);

	// generic function is called
	example_func_std("Hello", "Wold", "...");

	
	return 0;
}

