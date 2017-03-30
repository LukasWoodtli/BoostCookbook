cmake_minimum_required(VERSION 2.8.7)

project(BoostCookbook)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_COLOR_MAKEFILE   ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra  -Werror -std=c++11")

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE DEBUG)
endif()


find_package(Boost 1.53.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_executable(main main.c)

