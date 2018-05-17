cmake_minimum_required (VERSION 2.8.7)

add_library(myLib SHARED MyLib.cpp)
target_compile_options(myLib PUBLIC "-fvisibility=hidden" PRIVATE "-DMY_LIBRARY_LINK_DYNAMIC")
if (NOT APPLE)
	# version scripts (export maps) are not supported by ld on macOS
	target_link_libraries(myLib -Wl,--version-script=${CMAKE_CURRENT_LIST_DIR}/export.map)
endif()

add_executable(ExportImportFunctionsAndClasses main.cpp)
target_link_libraries(ExportImportFunctionsAndClasses myLib)

add_test(ExportImportFunctionsAndClasses ExportImportFunctionsAndClasses)
