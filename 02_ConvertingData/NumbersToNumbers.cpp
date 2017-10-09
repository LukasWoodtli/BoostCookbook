#include <iostream>
#include <cstdlib>
#include <ctime>

#include <boost/numeric/conversion/cast.hpp>

bool some_extremely_rare_condition() {
  return std::rand() % 5 == 0;
}

bool another_extremely_rare_condition() {
  return std::rand() % 3 == 0;
}


int foo() {
  if (some_extremely_rare_condition()) {
    return -1;
  }
  else if (another_extremely_rare_condition()) {
    return 1000000;
  }

  return 65535;
}

void some_function(unsigned short param) {
  (void)param;
}

void correct_implementation() {
  some_function(boost::numeric_cast<unsigned short>(foo()));
}

void test_function() {
  for (unsigned int i = 0; i < 100; ++i) {
    try {
      correct_implementation();
    }
    catch (const boost::numeric::bad_numeric_cast& e) {
      std::cout << '#' << i << ' ' << e.what() << '\n';
    }
  }
}


void test_function1() {
  for (unsigned int i = 0; i < 100; ++i) {
    try {
      correct_implementation();
    }
    catch (const boost::numeric::positive_overflow& e) {
      std::cout << "POS OVERFLOW in #" << i << ' ' << e.what() << '\n';
    }
    catch (const boost::numeric::negative_overflow& e) {
      std::cout << "NEG OVERFLOW in #" << i << ' ' << e.what() << '\n';
    }
  }
}



template <class SourceT, class TargetT>
struct mythrow_overflow_handler {
  void operator()(boost::numeric::range_check_result r) {
    if (r != boost::numeric::cInRange) {
      throw std::logic_error("Not in range!");
    }
  }
};

template <class TargetT, class SourceT>
TargetT my_numeric_cast(const SourceT& in) {
  using namespace boost;

  typedef numeric::conversion_traits<TargetT, SourceT> conv_traits;

  typedef boost::numeric::converter<TargetT, SourceT, conv_traits,
    mythrow_overflow_handler<SourceT, TargetT>> converter;

    return converter::convert(in);
}


int main() {
  std::srand(std::time(0));

  test_function();

  std::cout << "\n==============================\n\n";

   test_function1();

   std::cout << "\n==============================\n\n";

   try {
     my_numeric_cast<short>(1000000);
  }
  catch (const  std::logic_error& e) {
    std::cout << "It works! " << e.what() << '\n';
  }
}
