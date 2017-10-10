cmake_minimum_required (VERSION 2.8.7)

add_executable(StringsToNumbers StringsToNumbers.cpp)
add_test(StringsToNumbers StringsToNumbers)

add_executable(NumbersToStrings NumbersToStrings.cpp)
add_test(NumbersToStrings NumbersToStrings)

add_executable(NumbersToNumbers NumbersToNumbers.cpp)
add_test(NumbersToNumbers NumbersToNumbers)

add_executable(UserdefinedTypes UserdefinedTypes.cpp)
add_test(UserdefinedTypes UserdefinedTypes)
