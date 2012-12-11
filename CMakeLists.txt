cmake_minimum_required(VERSION 2.8.5)
project(dtcc2tests)

#SET(CMAKE_C_COMPILER "clang")
#SET(CMAKE_CXX_COMPILER "clang")

if(NOT DEFINED FLEX_EXECUTABLE)
    find_program(FLEX_EXECUTABLE NAMES flex.exe flex)
endif()
if(NOT DEFINED BISON_EXECUTABLE)
    find_program(BISON_EXECUTABLE NAMES bison.exe bison)
endif()

# Find Bison and Flex
find_package(FLEX)
find_package(BISON)

bison_target(libdcpu-ci-lang-c-parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "-d -y")
flex_target(libdcpu-ci-lang-c-lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS \"--header-file=${CMAKE_CURRENT_BINARY_DIR}/lexer.hpp\")
add_flex_bison_dependency(libdcpu-ci-lang-c-lexer libdcpu-ci-lang-c-parser)

FILE(GLOB nodesSrc nodes/*.cpp)
FILE(GLOB nodesHdr nodes/*.h)
FILE(GLOB visitorSrc visitor/*.cpp)
FILE(GLOB visitorHrd visitor/*.h)
FILE(GLOB typesSrc types/*.cpp)
FILE(GLOB typesHrd types/*.h)
FILE(GLOB symboltableSrc symboltable/*.cpp)
FILE(GLOB symboltableHrd symboltable/*.h)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FLEX_UNISTD_INCLUDE}
)

add_subdirectory(nodes)
add_subdirectory(visitor)
add_subdirectory(types)
add_subdirectory(errors)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.h ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.cpp
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tool-errgen ${CMAKE_CURRENT_SOURCE_DIR}/errors/err.d ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.h ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.cpp
    COMMENT "Generating error definition files..."
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/errors/err.d
    )

add_executable(dtcc2tests
    main.cpp
    ${FLEX_libdcpu-ci-lang-c-lexer_OUTPUTS}
    ${BISON_libdcpu-ci-lang-c-parser_OUTPUTS}
    parser.y
    lexer.l
    errors/derr.defs.h
    errors/derr.defs.cpp
    errors/ErrorList.cpp
    errors/ErrorList.h
    valuetypes/LValue.h
    valuetypes/LValue.cpp
    valuetypes/RValue.h
    valuetypes/CValue.h
    valuetypes/ValueType.h
    valuetypes/FunctionDesignator.h
    valuetypes/IsValueTypeHelper.h
    valuetypes/IsValueTypeHelper.cpp
    valuetypes/PromotionHelper.h
    valuetypes/PromotionHelper.cpp
    valuetypes/ConstHelper.cpp
    valuetypes/ConstHelper.h
    ${nodesHdr}
    ${nodesSrc}
    ${visitorHdr}
    ${visitorSrc}
    ${typesHdr}
    ${typesSrc}
    ${symboltableHrd}
    ${symboltableSrc}
)
