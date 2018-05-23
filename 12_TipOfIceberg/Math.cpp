#include <cassert>

#include <boost/math/special_functions.hpp>


template <class T>
bool check_float_inputs(T value) {
	auto ret = (not boost::math::isinf(value)) && (not boost::math::isnan(value));

	if (boost::math::signbit(value)) {
		value = boost::math::changesign(value);
	}

	return ret;
}

int main() {
	auto ret = check_float_inputs(std::sqrt(-1.0));
	assert(not ret);

	ret = check_float_inputs(std::numeric_limits<double>::max() * 2.0);
	assert(not ret);
}
