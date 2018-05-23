cmake_minimum_required (VERSION 2.8.7)


add_executable(Graphs Graphs.cpp)
add_test(Graphs Graphs)

add_executable(Random Random.cpp)
target_link_libraries(Random ${Boost_RANDOM_LIBRARY})
add_test(Random Random)

add_executable(Math Math.cpp)
add_test(Math Math)


add_executable(Test Test1.cpp Test2.cpp TestMain.cpp)
target_compile_definitions(Test PRIVATE -DBOOST_TEST_DYN_LINK)
target_link_libraries(Test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(Test Test)
