cmake_minimum_required (VERSION 2.8.7)


add_executable(Strings Strings.cpp)
add_test(Strings Strings)

add_executable(RegexMatch RegexMatch.cpp)
target_link_libraries(RegexMatch ${Boost_REGEX_LIBRARY})

add_executable(RegexSearchReplace RegexSearchReplace.cpp)
target_link_libraries(RegexSearchReplace ${Boost_REGEX_LIBRARY})

add_executable(SafePrintf SafePrintf.cpp)
add_test(SafePrintf SafePrintf)

add_executable(ReplaceEraseStrings ReplaceEraseStrings.cpp)
add_test(ReplaceEraseStrings ReplaceEraseStrings)

add_executable(StringIterators StringIterators.cpp)
add_test(StringIterators StringIterators)

add_executable(StringRefs StringRefs.cpp)
add_test(StringRefs StringRefs)
