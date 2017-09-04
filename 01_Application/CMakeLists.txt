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

add_executable(BoostArray BoostArray.cpp)
add_test(BoostArray BoostArray)

add_executable(BoostTuple BoostTuple.cpp)
add_test(BoostTuple BoostTuple)

add_executable(BoostBind BoostBind.cpp)
add_test(BoostBind BoostBind)

add_executable(BoostBind2 BoostBind2.cpp)
add_test(BoostBind2 BoostBind2)

add_executable(BoostMove BoostMove.cpp)
add_test(BoostMove BoostMove)

add_executable(BoostMovableButNotCopyable BoostMovableButNotCopyable.cpp)
add_test(BoostMovableButNotCopyable BoostMovableButNotCopyable) 

