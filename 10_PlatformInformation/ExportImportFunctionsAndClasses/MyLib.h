#pragma once

#include <boost/config.hpp>

#if defined(MY_LIBRARY_LINK_DYNAMIC)
# if defined(MY_LIBRARY_COMPILATION)
#  define MY_LIBRARY_API BOOST_SYMBOL_EXPORT
# else
#  define MY_LIBRARY_API BOOST_SYMBOL_IMPORT
# endif
#else
# define MY_LIBRARY_API
#endif


#include <exception>

int MY_LIBRARY_API foo();

class MY_LIBRARY_API bar {
public:
	int meow() const;
};


// Exceptions must always be visible!!!
struct BOOST_SYMBOL_VISIBLE bar_exception : public std::exception {
	
};
