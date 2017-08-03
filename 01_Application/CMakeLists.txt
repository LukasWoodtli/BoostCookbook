cmake_minimum_required (VERSION 2.8.7)


add_executable(ProgramOptions ProgramOptions.cpp)
target_link_libraries(ProgramOptions boost_program_options)

add_executable(BoostAny BoostAny.cpp)
add_test(BoostAny BoostAny)

add_executable(BoostVariant BoostVariant.cpp)
add_test(BoostVariant BoostVariant)

add_executable(StaticVisitor StaticVisitor.cpp)
add_test(StaticVisitor StaticVisitor)

add_executable(BoostOptional BoostOptional.cpp)
add_test(BoostOptional BoostOptional)

