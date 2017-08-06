#include <boost/bind.hpp>
#include <functional>
#include <vector>
#include <iostream>

class Number {
  friend Number operator+(Number a, Number b);
  friend std::ostream& operator<<(std::ostream& stream, const Number& n);
public:
    Number(int num=0) : _num(num) {}
    void operator<<(std::ostream& stream) {stream << _num;}
private:
  int _num;
};

inline Number operator+(Number a, Number b) {
  return Number(a._num + b._num);
}

inline std::ostream& operator<<(std::ostream& stream, const Number& n) {
  stream << n._num;
  return stream;
}

struct mul_2_func_obj : std::unary_function<Number, Number> {
  Number operator()(Number& n1) const {
    return n1 + n1;
  }
};

void mul_2_impl1(std::vector<Number>& values) {
  mul_2_func_obj mul_2_func;
  for (auto &val: values)
    std::cout << mul_2_func(val) << "\n";
}


// using Binding
void mul_2_impl2(std::vector<Number>& values) {
  auto mul2 = boost::bind(std::plus<Number>(), _1, _1);
  for(auto &val: values){
    std::cout << mul2(val) << '\n';
  }
}

template <class T>
void mul_2_impl3(std::vector<T>& values) {
  auto mul2 = boost::bind(std::plus<T>(), _1, _1);
  for(auto &val: values) {
    std::cout << mul2(val) << '\n';
  }
}



class Device1 {
private:
  short temperature() { return 1;}
  short wetness() { return 4;}
  int illumination() { return 7;}
  int atmospheric_pressure() { return 9;}
  void wait_for_data() {}

public:
  template<class FuncT>
  void watch(const FuncT& f) {
    int i = 0;
    for (;;) {
      wait_for_data();
      f(
        temperature(),
        wetness(),
        illumination(),
        atmospheric_pressure()
      );
      if (++i > 3)
        break;
    }
  }
};


class Device2 {
private:
  short temperature() { return 1;}
  short wetness() { return 4;}
  int illumination() { return 7;}
  int atmospheric_pressure() { return 9;}
  void wait_for_data() {}

public:
  template<class FuncT>
  void watch(const FuncT& f) {
    int i = 0;
    for (;;) {
      wait_for_data();
      f(
        wetness(),
        temperature(),
        atmospheric_pressure(),
        illumination()
      );
      if (++i > 3)
        break;
    }
  }
};

void detect_storm(int wetness, int temperature,
    int atmospheric_pressure, int illumination) {
  std::cout << "================\n";
  std::cout << "Wetness: " << wetness << "\n";
  std::cout << "Temperature: " << temperature << "\n";
  std::cout << "Atmospheric Pressure: " << atmospheric_pressure << "\n";
  std::cout << "Illumination: " << illumination << "\n";
  std::cout << "================\n\n";
}


int main() {
  std::vector<Number> vals = {1,2,3,4,5};
  mul_2_impl1(vals);
  mul_2_impl2(vals);
  mul_2_impl3(vals);



  Device1 d1;
  d1.watch(boost::bind(&detect_storm, _2, _1, _4, _3));

  Device2 d2;
  d2.watch(boost::bind(&detect_storm, _1, _2, _3, _4));
}
