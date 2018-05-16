cmake_minimum_required (VERSION 2.8.7)


add_executable(DetectingCompilerSupport DetectingCompilerSupport.cpp)
add_test(DetectingCompilerSupport DetectingCompilerSupport)

add_Subdirectory("ExportImportFunctionsAndClasses")
