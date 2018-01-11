#include <boost/scoped_array.hpp>
#include <memory>
#include <iostream>

struct my_type {
  ~my_type() { std::cout << "Delete\n"; }
};

void foo_fixed_boost() {
  boost::scoped_array<my_type> buffer(new my_type[3]);

  // do something here ...

  // dtor of buffer will call delete[]
}

// C++11 style
void foo_fixed_std() {
  std::unique_ptr<my_type[]> buffer(new my_type[3]);

  // do something here ...

  // dtor of buffer will call delete[]
}

int main() {
  std::cout << "Call foo_fixed_boost\n";
  foo_fixed_boost();

  std::cout << "Call foo_fixed_std\n";
  foo_fixed_std();

}
