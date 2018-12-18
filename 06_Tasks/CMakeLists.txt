cmake_minimum_required (VERSION 2.8.7)


add_executable(Task Task.cpp)
target_link_libraries(Task ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(Task Task)

add_executable(Timers Timers.cpp)
target_link_libraries(Timers ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)

