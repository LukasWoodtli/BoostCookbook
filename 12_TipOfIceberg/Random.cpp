#include <string>
#include <iostream>

#include <boost/config.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

/* See also:
 * http://en.cppreference.com/w/cpp/numeric/random
 */

static const std::string provider =
#ifdef BOOST_WINDOWS
	"Microsoft Strong Cryptographic Provider";
#else
	"/dev/urandom";		// '/dev/random' would be more secure but block until enough events are collected from os/hw to construct a random number
#endif

int main() {

 	boost::random_device device(provider);

	// uniform distribution, returns value between 1000 and 65535
	boost::random::uniform_int_distribution<unsigned short> random(1000);

	std::cout << random(device) << '\n';
}
