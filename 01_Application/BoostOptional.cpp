#include <boost/optional.hpp>
#include <iostream>
#include <stdlib.h>

class locked_device {
  explicit locked_device(const char* param) {
    (void)param;
    std::cout << "Device is locked\n";
  }

public:
  ~locked_device() {
    // releasing device lock
  }

  void use() {
    std::cout << "Success!\n";
  }

  static boost::optional<locked_device> try_lock_device() {
    if (rand() % 2) {
      // Failed to lock device
      return boost::none;
    }

    // Success!
    return locked_device("device name");
  }

};


int main() {
  srandom(5);

  for (unsigned i = 0; i < 10; ++i) {
    boost::optional<locked_device> t = locked_device::try_lock_device();

    if (t) {
      t->use();
      return 0;
    } else {
      std::cout << "... trying again\n";
    }
  }
  std::cout << "Failure!\n";
  return -1; // could fail on travis-ci
}
