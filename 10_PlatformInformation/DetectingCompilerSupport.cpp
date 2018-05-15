#include <cassert>
#include <boost/config.hpp>


//////////////////////////
// int 128 ///////////////
//////////////////////////

#ifdef BOOST_HAS_INT128

typedef boost::int128_type int128_t;
typedef boost::uint128_type uint128_t;

inline int128_t mul(int128_t v1, int128_t v2, int128_t v3) {
	return v1 * v2 * v3;
}

#else

# ifdef BOOST_NO_LONG_LONG
#  error This code requires at leas int64_t support
# endif

// custom int128 arithmetic
struct int128_t { boost::long_long_type hi, lo; };
struct uint128_t { boost::ulong_long_type hi, lo; };

inline int128_t mul(int128_t v1, int128_t v2, int128_t v3) {
	(void)v1;
	(void)v2;
	(void)v3;

	return 0; // hand written math
}

#endif




//////////////////////////
// RTTI //////////////////
//////////////////////////

#if !defined(BOOST_NO_RTTI) && !defined(BOOST_NO_CXX11_HDR_TYPEINDEX)

#include <typeindex>

using std::type_index;

template<class T>
type_index type_id() {
	return typeid(T);
}


#else

#include <cstring>
#include <boost/current_function.hpp>

struct type_index {
	const char* name_;
	explicit type_index(const char* name) : name_(name) {}
};

inline bool operator== (const type_index& v1, const type_index& v2) {
	return !std::strcmp(v1.name_, v2.name_);
}

inline bool operator!= (const type_index& v1, const type_index& v2) {
	// !! needed to supress warnings
	return !!std::strcmp(v1.name_, v2.name_);
}


template <class T>
inline type_index type_id() {
	return type_index(BOOST_CURRENT_FUNCTION);
}

#endif



int main() {
	assert(type_id<unsigned int>() == type_id<unsigned>());
	assert(type_id<double>() != type_id<long double>());
}
