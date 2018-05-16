#define MY_LIBRARY_COMPILATION
#include "MyLib.h"

int myHiddenFunction() {
	return 23;
}

int MY_LIBRARY_API foo() {
	return myHiddenFunction();
}

int bar::meow() const {
	throw bar_exception();
	return 42;
}

