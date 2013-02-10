cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)


# set warning level to Wall or /W4
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()


if(NOT DEFINED FLEX_EXECUTABLE)
    find_program(FLEX_EXECUTABLE NAMES flex.exe flex)
endif()
if(NOT DEFINED BISON_EXECUTABLE)
    find_program(BISON_EXECUTABLE NAMES bison.exe bison)
endif()

# Find Bison and Flex
find_package(FLEX)
find_package(BISON)

# build parser and lexer using flex and bison
bison_target(dcpu-cc-parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "-d -y")
flex_target(dcpu-cc-lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS \"--header-file=${CMAKE_CURRENT_BINARY_DIR}/lexer.hpp\")
add_flex_bison_dependency(dcpu-cc-lexer dcpu-cc-parser)



include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FLEX_UNISTD_INCLUDE}
)

add_subdirectory(errors/errgen)

# build command for generating errors
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.h ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.cpp
    COMMAND dcpucc-errgen ${CMAKE_CURRENT_SOURCE_DIR}/errors/err.d ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.h ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.cpp
    COMMENT "Generating error definition files..."
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/errors/err.d dcpucc-errgen
    )


add_subdirectory(astnodes)
add_subdirectory(visitor)
add_subdirectory(types)
add_subdirectory(errors)
add_subdirectory(codegen)
add_subdirectory(symboltable)
add_subdirectory(valuetypes)

add_library(libdcpu-cc
    Compiler.cpp
    ${FLEX_dcpu-cc-lexer_OUTPUTS}
    ${BISON_dcpu-cc-parser_OUTPUTS}
    parser.y
    lexer.l
    ${ERRORS_HEADER}
    ${ERRORS_SOURCE}
    ${VALUETYPES_HEADER}
    ${VALUETYPES_SOURCE}
    ${NODES_HEADERS}
    ${NODES_SOURCE}
    ${VISITOR_HEADER}
    ${VISITOR_SOURCE}
    ${TYPES_HEADER}
    ${TYPES_SOURCE}
    ${SYMBOLTABLE_HEADER}
    ${SYMBOLTABLE_SOURCE}
    ${CODEGEN_HEADER}
    ${CODEGEN_SOURCE}
)

add_dependencies(libdcpu-cc
    errors/derr.defs.h
    )

# to avoid double "liblib"
set_target_properties(libdcpu-cc PROPERTIES PREFIX "")
