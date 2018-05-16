cmake_minimum_required (VERSION 2.8.7)


add_executable(FilesAndDirs FilesAndDirs.cpp)
target_link_libraries(FilesAndDirs  ${Boost_SYSTEM_LIBRARY} -lboost_filesystem)
add_test(FilesAndDirs FilesAndDirs)
