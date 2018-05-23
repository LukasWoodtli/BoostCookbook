#define BOOST_TEST_MODULE test_module_name
#include <boost/test/unit_test.hpp>

#include <stdexcept>

struct foo {
	int val_;

	operator int() const { return val_; }
	bool is_not_null() const { return val_ != 0; }
	void throws() const { throw std::logic_error("bla"); }
};


BOOST_AUTO_TEST_CASE(test_no_1) {
	foo f1 = {1}, f2 = {2};
	BOOST_CHECK(f1.is_not_null());

	BOOST_CHECK_NE(f1, f2);

	BOOST_CHECK_THROW(f1.throws(), std::logic_error);
}
