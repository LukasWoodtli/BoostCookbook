cmake_minimum_required (VERSION 2.8.7)

# shared_mutex is available from C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CreateThread CreateThread.cpp)
target_link_libraries(CreateThread  ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(CreateThread CreateThread)

add_executable(Mutex Mutex.cpp)
target_link_libraries(Mutex ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(Mutex Mutex)

add_executable(Atomic Atomic.cpp)
target_link_libraries(Atomic ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(Atomic Atomic)

add_executable(WorkQueue WorkQueue.cpp)
target_link_libraries(WorkQueue ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(WorkQueue WorkQueue)

add_executable(MultipleReadersSingleWriter MultipleReadersSingleWriter.cpp)
target_link_libraries(MultipleReadersSingleWriter ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(MultipleReadersSingleWriter MultipleReadersSingleWriter)

add_executable(ThreadLocal ThreadLocal.cpp)
target_link_libraries(ThreadLocal ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(ThreadLocal ThreadLocal)

add_executable(InterruptingThread InterruptingThread.cpp)
target_link_libraries(InterruptingThread ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(InterruptingThread InterruptingThread)

add_executable(ThreadGroup ThreadGroup.cpp)
target_link_libraries(ThreadGroup ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} -lpthread)
add_test(ThreadGroup ThreadGroup)
