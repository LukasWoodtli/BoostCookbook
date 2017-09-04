cmake_minimum_required(VERSION 2.8.7)

project(BoostCookbook)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES Clang)
	# See https://stackoverflow.com/questions/16655820/clang-mac-os-x-c11-linker-issue/16656234#16656234
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra  -Werror -std=c++11 -stdlib=libc++ -D'_LIBCPP_EXTERN_TEMPLATE(...)='")
else()
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra  -Werror -std=c++11")
endif()

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE DEBUG)
endif()


find_package(Boost 1.53.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_subdirectory("01_Application")

add_subdirectory("Other")


