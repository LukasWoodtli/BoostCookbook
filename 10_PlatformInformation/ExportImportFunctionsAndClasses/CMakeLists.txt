cmake_minimum_required (VERSION 2.8.7)

add_library(myLib SHARED MyLib.cpp)
target_compile_options(myLib PUBLIC "-fvisibility=hidden" PRIVATE "-DMY_LIBRARY_LINK_DYNAMIC")

add_executable(ExportImportFunctionsAndClasses main.cpp)
target_link_libraries(ExportImportFunctionsAndClasses myLib)

add_test(ExportImportFunctionsAndClasses ExportImportFunctionsAndClasses)
