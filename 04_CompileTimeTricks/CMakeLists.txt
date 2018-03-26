cmake_minimum_required (VERSION 2.8.7)


add_executable(TemplateFunctions TemplateFunctions.cpp)
add_test(TemplateFunctions TemplateFunctions)

add_executable(TypeFromNumber TypeFromNumber.cpp)
add_test(TypeFromNumber TypeFromNumber)

add_executable(TypeTraits TypeTraits.cpp)
add_test(TypeTraits TypeTraits)

add_executable(OperatorForTemplateParameter OperatorForTemplateParameter.cpp)
add_test(OperatorForTemplateParameter OperatorForTemplateParameter)
