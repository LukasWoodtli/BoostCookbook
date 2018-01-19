#include <functional>
#include <iostream>
#include <boost/function.hpp>

////////////////////////////////////////////////////////////////
// boost style /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
class int_processor {
  const int min_;
  const int max_;
  bool& triggered_;

public:
  int_processor(int min, int max, bool& triggered_)
    : min_(min),
      max_(max),
      triggered_(triggered_)
    {}

  void operator()(int i) const {
    if (i < min_ || i > max_) {
      triggered_ = true;
    }
  }
};

typedef boost::function<void(int)> fobject_t;

void process_integers(const fobject_t& f) {
    static const int data[] = {1, 2, 3, 4, 5, 200};
    std::for_each(data, data + sizeof(data), f);
}

// boost::function is convertible to bool
bool foo(const fobject_t& f) {
  if (f) {
    std::cout << "f is set\n";
    return true;
  } else {
    std::cout << "f is NOT set\n";
    return false;
  }
}

////////////////////////////////////////////////////////////////
// C++ 11 style ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
class int_processor_std {
  const int min_;
  const int max_;
  bool& triggered_;

public:
  int_processor_std(int min, int max, bool& triggered_)
    : min_(min),
      max_(max),
      triggered_(triggered_)
    {}

  void operator()(int i) const {
    if (i < min_ || i > max_) {
      triggered_ = true;
    }
  }
};

typedef std::function<void(int)> stdfobject_t;

void process_integers_std(const stdfobject_t& f) {
    if (not f) exit(EXIT_FAILURE);
    static const int data[] = {1, 2, 3, 4, 5, 200};
    std::for_each(data, data + sizeof(data), f);
}

// std::function is convertible to bool
bool foo_std(const stdfobject_t& f) {
  if (f) {
    std::cout << "f is set\n";
    return true;
  } else {
    std::cout << "f is NOT set\n";
    return false;
  }
}


#define ASSERT(b) do {if(not b) {std::cout << "ASSERT failed\n"; exit(EXIT_FAILURE);}}while(0)

int main() {
  // boost
  bool is_triggered = false;
  int_processor fo(0, 200, is_triggered);
  process_integers(fo);

#if !(defined(__linux__) && defined(__GNUC__))
  // this is not working on travis Linux/GCC
  ASSERT(is_triggered);
#endif

  // boost::function to bool conversion
  fobject_t empty;
  bool result = foo(empty);
  ASSERT(not result);
  result = foo(fo);
  ASSERT(result);

  // C++11
  is_triggered = false;
  int_processor_std fo_std(0, 200, is_triggered);
  process_integers_std(fo_std);
  ASSERT(is_triggered);

  // std::function to bool conversion
  stdfobject_t empty_std;
  result = foo_std(empty_std);
  ASSERT(not result);
  result = foo(fo_std);
  ASSERT(result);
}
