cmake_minimum_required (VERSION 2.8.7)


add_executable(Strings Strings.cpp)
add_test(Strings Strings)

add_executable(RegexMatch RegexMatch.cpp)
target_link_libraries(RegexMatch ${Boost_REGEX_LIBRARY})
