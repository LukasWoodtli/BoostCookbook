cmake_minimum_required(VERSION 3.0.1)

project(BoostCookbook)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE AND CMAKE_CXX_COMPILER_ID MATCHES Clang)
	# See https://stackoverflow.com/questions/16655820/clang-mac-os-x-c11-linker-issue/16656234#16656234
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra  -Werror -stdlib=libc++ -D'_LIBCPP_EXTERN_TEMPLATE(...)='")
else()
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra  -Werror")
endif()

if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE DEBUG)
endif()

find_package(Boost 1.53.0 REQUIRED thread system program_options regex)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

add_subdirectory("01_Application")
add_subdirectory("02_ConvertingData")
add_subdirectory("03_ManagingResources")
add_subdirectory("04_CompileTimeTricks")
add_subdirectory("05_Threads")
add_subdirectory("06_Tasks")
add_subdirectory("07_Strings")
add_subdirectory("08_Metaprogramming")
add_subdirectory("09_Containers")

add_subdirectory("Other")
