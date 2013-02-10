cmake_minimum_required(VERSION 2.8.5)

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
