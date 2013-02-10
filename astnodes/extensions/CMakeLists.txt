cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)

# Set header .h files
SET (NODES_EXT_HEADERS
    astnodes/extensions/AssemblyStatement.h
    astnodes/extensions/BuiltInVaStart.h
PARENT_SCOPE)

# Set source .cpp files
set (NODES_EXT_SOURCE
    astnodes/extensions/AssemblyStatement.cpp
    astnodes/extensions/BuiltInVaStart.cpp
PARENT_SCOPE) 

