cmake_minimum_required (VERSION 2.8.7)


add_executable(ComparingStrings ComparingStrings.cpp)
add_test(ComparingStrings ComparingStrings)

add_executable(UnorderedSetAndMap UnorderedSetAndMap.cpp)
add_test(UnorderedSetAndMap UnorderedSetAndMap)

add_executable(Bimap Bimap.cpp)
add_test(Bimap Bimap)

add_executable(SList SList.cpp)
target_link_libraries(SList ${Boost_SYSTEM_LIBRARY})
add_test(SList SList)
