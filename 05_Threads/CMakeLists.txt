cmake_minimum_required (VERSION 2.8.7)


add_executable(CreateThread CreateThread.cpp)
target_link_libraries(CreateThread  ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(CreateThread CreateThread)

add_executable(Mutex Mutex.cpp)
target_link_libraries(Mutex ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(Mutex Mutex)

add_executable(Atomic Atomic.cpp)
target_link_libraries(Atomic ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(Atomic Atomic)
