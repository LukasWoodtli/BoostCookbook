#include <boost/array.hpp>
#include <algorithm>
#include <iostream>

struct add_1 : std::unary_function<char, void> {
  void operator()(char& c) const {
    ++c;
  }
};


typedef boost::array<char, 4> array4_t;

array4_t& vector_advance(array4_t& val) {
  std::for_each(val.begin(), val.end(), add_1());
  return val;
}


int main() {
  array4_t val = {{0, 1, 2, 3}};

  array4_t val_res;
  val_res = vector_advance(val);

  assert(val.size() == 4);
  assert(val[0] == 1);
  assert(sizeof(val) == sizeof(char) * array4_t::static_size);

  assert(val_res.size() == 4);
  assert(val_res[0] == 1);
  assert(sizeof(val_res) == sizeof(char) * array4_t::static_size);

  return 0;
}
