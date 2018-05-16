#include "MyLib.h"

#include <cassert>


int main() {

	assert(foo() == 23);

	bar b;
	try {
		b.meow();
		// should not get here
		return -1;
	}
	catch (const bar_exception&) {
		
	}
	catch (...) {
		// should not get here
		return -1;
	}
	
}
