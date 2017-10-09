#include <string>
#include <boost/lexical_cast.hpp>


int main() {
  std::string s = boost::lexical_cast<std::string>(100);
  assert(s == "100");
}
