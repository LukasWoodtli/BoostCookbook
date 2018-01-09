#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <iostream>
#include <string>

class foo_class {
public:
  void print() { std::cout << "foo_class\n"; }
};

foo_class *get_data() {
  static int i = 0;
  if (i < 5) {
    ++i;
    return new foo_class;
  }

  return NULL;
}


void process_sp1(const boost::shared_ptr<foo_class>& p) { std::cout << __FUNCTION__ << "\n"; p->print(); }
void process_sp2(const boost::shared_ptr<foo_class>& p) { std::cout << __FUNCTION__ << "\n"; p->print(); }
void process_sp3(const boost::shared_ptr<foo_class>& p) { std::cout << __FUNCTION__ << "\n"; p->print(); }

void foo2() {
  typedef boost::shared_ptr<foo_class> ptr_t;
  ptr_t p;

  while (p = ptr_t(get_data())) {
    boost::thread(boost::bind(&process_sp1, p)).detach();
    boost::thread(boost::bind(&process_sp2, p)).detach();
    boost::thread(boost::bind(&process_sp3, p)).detach();
  }
}


void process_str1(boost::shared_ptr<std::string> p) { std::cout << __FUNCTION__ << ": " << *p << "\n"; }
void process_str2(const boost::shared_ptr<std::string>& p) { std::cout << __FUNCTION__ << ": " <<  *p << "\n"; }

void foo3() {
  boost::shared_ptr<std::string> ps = boost::make_shared<std::string>("Test\n");

  boost::thread(boost::bind(&process_str1, ps)).detach();
  boost::thread(boost::bind(&process_str2, ps)).detach();
}

int main() {
  foo2();
  foo3();

  // poor man's synchronization
  sleep(5);

  return 0;
}
