#pragma once

#include <stdexcept>

struct foo {
	int val_;

	operator int() const { return val_; }
	bool is_not_null() const { return val_ != 0; }
	void throws() const { throw std::logic_error("bla"); }
};
