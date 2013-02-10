cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)


add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.h ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.cpp
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tool-errgen ${CMAKE_CURRENT_SOURCE_DIR}/errors/err.d ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.h ${CMAKE_CURRENT_SOURCE_DIR}/errors/derr.defs.cpp
    COMMENT "Generating error definition files..."
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/errors/err.d
    PARENT_SCOPE)

# Set header .h files
SET (ERRORS_HEADER
    errors/derr.defs.h
    errors/ErrorList.h
PARENT_SCOPE)

# Set source .cpp files
set (ERRORS_SOURCE
    errors/derr.defs.cpp
    errors/ErrorList.cpp
PARENT_SCOPE) 
