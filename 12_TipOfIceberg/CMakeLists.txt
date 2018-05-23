cmake_minimum_required (VERSION 2.8.7)


add_executable(Graphs Graphs.cpp)
add_test(Graphs Graphs)

add_executable(Random Random.cpp)
target_link_libraries(Random ${Boost_RANDOM_LIBRARY})
add_test(Random Random)
