cmake_minimum_required (VERSION 2.8.7)


add_executable(FilesAndDirs FilesAndDirs.cpp)
target_link_libraries(FilesAndDirs  ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
add_test(FilesAndDirs FilesAndDirs)

add_executable(InterProcessCommunication InterProcessCommunication.cpp)
target_link_libraries(InterProcessCommunication -lpthread)
if (NOT APPLE)
	target_link_libraries(InterProcessCommunication -lrt)
endif()

if (APPLE)
	# on travis boost on linux is to old to support boost::coroutines2
	add_executable(Coroutines Coroutines.cpp)
	target_link_libraries(Coroutines ${Boost_CONTEXT_LIBRARY})
	add_test(Coroutines Coroutines)
endif()
