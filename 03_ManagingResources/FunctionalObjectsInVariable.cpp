#include <functional>
#include <iostream>
#include <boost/function.hpp>
#include <exception>

////////////////////////////////////////////////////////////////
// boost style /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
class int_processor : public std::unary_function<int, void> {
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

#define TEST_PRINT(t) do{std::cout << "TEST " << #t << "\n";} while (0)

int main() {
 try {
  TEST_PRINT(1);
  // boost
  bool is_triggered = false;
  int_processor fo(0, 200, is_triggered);
  process_integers(fo);
  ASSERT(is_triggered);

  TEST_PRINT(2);
  // boost::function to bool conversion
  fobject_t empty;
  bool result = foo(empty);
  ASSERT(not result);
  result = foo(fo);
  ASSERT(result);

  TEST_PRINT(3);
  // C++11
  is_triggered = false;
  int_processor_std fo_std(0, 200, is_triggered);
  process_integers_std(fo_std);
  ASSERT(is_triggered);

  TEST_PRINT(4);
  // std::function to bool conversion
  stdfobject_t empty_std;
  result = foo_std(empty_std);
  ASSERT(not result);
  result = foo(fo_std);
  ASSERT(result);
  TEST_PRINT(5);
 }
 catch(const std::exception& e) {
     std::cout << e.what();
 }
 TEST_PRINT(6);
}
