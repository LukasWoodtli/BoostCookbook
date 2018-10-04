cmake_minimum_required (VERSION 2.8.7)


add_executable(icl icl.cpp)
add_test(icl icl)

add_executable(boost_range boost_range.cpp)
add_test(boost_range boost_range)

add_executable(boost_transform boost_transform.cpp)
add_test(boost_transform boost_transform)

