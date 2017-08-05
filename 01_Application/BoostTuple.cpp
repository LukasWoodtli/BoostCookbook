#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <string>
#include <set>
#include <cassert>

using namespace boost;

int main () {
  boost::tuple<int, std::string> almost_a_pair(10, "Hello");
  boost::tuple<int, float, double, int> quad(10, 1.0f, 10.0, 1);

  int i = boost::get<0>(almost_a_pair);
  assert(i == 10);
  const std::string& str = boost::get<1>(almost_a_pair);
  assert(str == "Hello");
  double d = boost::get<2>(quad);
  assert(d == 10.0);

  std::set<tuple<int, double, int>> s;
  s.insert(make_tuple(1, 1.0, 2));
  s.insert(make_tuple(2, 10.0, 2));
  s.insert(make_tuple(3, 100.0, 2));

  auto t = make_tuple(0, -1.0, 2);
  assert(2 == get<2>(t));


  boost::tuple<int, float, double, int> quad2(10, 1.0f, 10.0, 1);
  int i2 = 0;
  float f = 0.0f;
  double d2 = 0.0;
  int i3 = 0;;

  boost::tie(i2, f, d2, i3) = quad2;
  assert(i2 == 10);
  assert(i3 == 1);


  return 0;
}
