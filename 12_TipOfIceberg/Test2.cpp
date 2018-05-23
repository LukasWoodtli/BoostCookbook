#include <boost/test/unit_test.hpp>

#include "FooToTest.h"

BOOST_AUTO_TEST_CASE(test_throw) {
	foo f1 = {1};
	BOOST_CHECK_THROW(f1.throws(), std::logic_error);
}
