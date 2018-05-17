cmake_minimum_required (VERSION 2.8.7)


add_executable(FilesAndDirs FilesAndDirs.cpp)
target_link_libraries(FilesAndDirs  ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
add_test(FilesAndDirs FilesAndDirs)

add_executable(InterProcessCommunication InterProcessCommunication.cpp)
target_link_libraries(InterProcessCommunication -lpthread)
if (NOT APPLE)
	target_link_libraries(InterProcessCommunication -lrt)
endif()
