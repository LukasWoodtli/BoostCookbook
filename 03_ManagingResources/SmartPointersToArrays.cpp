#include <boost/scoped_array.hpp>
#include <boost/shared_array.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <cstring>
#include <iostream>


struct my_type {
  ~my_type() { std::cout << "Delete\n"; }
};

///////////////////////////////////////////////////////////////
// Section
// Managing pointers to arrays that do not leave scope
///////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////
// Section:
// Reference counting pointers to arrays used across methods
///////////////////////////////////////////////////////////////
void do_process(const boost::shared_array<my_type> & data, std::size_t size) {
  // do some processing
  (void)data;
  (void)size;
}

void do_process_in_background_v1(const my_type* data, std::size_t size) {
  // copy data
  boost::shared_array<my_type> data_cpy(new my_type[size]);
  std::memcpy(data_cpy.get(), data, size);

  boost::thread(boost::bind(&do_process, data_cpy, size)).detach();
}


void do_process_shared_ptr(const boost::shared_ptr<my_type[]> & data, std::size_t size) {
  // do some processing
  (void)data;
  (void)size;
}

void do_process_in_background_v2(const my_type* data, std::size_t size) {
  // copy data
  boost::shared_ptr<my_type[]> data_cpy = boost::make_shared<my_type[]>(size);
  std::memcpy(data_cpy.get(), data, size);

  boost::thread(boost::bind(&do_process_shared_ptr, data_cpy, size)).detach();
}


void do_process_shared_ptr2(const boost::shared_ptr<my_type> & data, std::size_t size) {
  // do some processing
  (void)data;
  (void)size;
}

void do_process_in_background_v3(const my_type* data, std::size_t size) {
  // copy data
  // same as version 2 but with custom deleter
  boost::shared_ptr<my_type> data_cpy(new my_type[size],
                                      boost::checked_array_deleter<my_type>());
  std::memcpy(data_cpy.get(), data, size);

  boost::thread(boost::bind(&do_process_shared_ptr2, data_cpy, size)).detach();
}


// C++11 style
void do_process_shared_std(const std::shared_ptr<my_type[]> & data, std::size_t size) {
  // do some processing
  (void)data;
  (void)size;
}

void do_process_in_background_std(const my_type* data, std::size_t size) {
  // copy data
  // std::make_shared<my_type[]>(size) not available until C++20
  std::shared_ptr<my_type[]> data_cpy(new my_type[size]);
  std::memcpy(data_cpy.get(), data, size);

  boost::thread(boost::bind(&do_process_shared_std, data_cpy, size)).detach();
}

///////////////////////////////////////////////////////////////
// tests
///////////////////////////////////////////////////////////////

int main() {

  std::cout << "Call foo_fixed_boost\n";
  foo_fixed_boost();

  std::cout << "\nCall foo_fixed_std\n";
  foo_fixed_std();



  constexpr size_t SIZE = 3;
  my_type my_array[SIZE] = {};
  std::cout << "\n\nCall do_process_in_background_v1\n";
  do_process_in_background_v1(my_array, SIZE);

  //sleep(1);
  std::cout << "\nCall do_process_in_background_v2\n";
  do_process_in_background_v2(my_array, SIZE);

  //sleep(1);
  std::cout << "\nCall do_process_in_background_v3\n";
  do_process_in_background_v3(my_array, SIZE);

  //sleep(1);
  std::cout << "\nCall do_process_in_background_std (C++11)\n";
  do_process_in_background_std(my_array, SIZE);

  //sleep(3);
  std::cout << "\nEnd!\n";

}
