cmake_minimum_required (VERSION 2.8.7)

add_executable(StringsToNumbers StringsToNumbers.cpp)
add_test(StringsToNumbers StringsToNumbers)

add_executable(NumbersToStrings NumbersToStrings.cpp)
add_test(NumbersToStrings NumbersToStrings)

add_executable(NumbersToNumbers NumbersToNumbers.cpp)
add_test(NumbersToNumbers NumbersToNumbers)

add_executable(UserdefinedTypes UserdefinedTypes.cpp)
add_test(UserdefinedTypes UserdefinedTypes)

add_executable(PolymorphicTypes PolymorphicTypes.cpp)
add_test(PolymorphicTypes PolymorphicTypes)

add_executable(ParsingSimpleInput ParsingSimpleInput.cpp)
add_test(ParsingSimpleInput ParsingSimpleInput)

add_executable(ParsingInput ParsingInput.cpp)

# This test has an segfault on travis.ci with linux and gcc
if (NOT
    ((UNIX AND NOT APPLE) # Linux
    AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))) # GCC
  add_test(ParsingInput ParsingInput)
endif()
