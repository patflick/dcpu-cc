cmake_minimum_required(VERSION 2.8.5)
project(dtcc2tests)


# Set header .h files
SET (SYMBOLTABLE_HEADER
    symboltable/SymbolObject.h
    symboltable/SymbolTable.h
    symboltable/SymbolTableScope.h
    symboltable/SymbolTypes.h
    symboltable/TypePosition.h
PARENT_SCOPE)

# Set source .cpp files
set (SYMBOLTABLE_SOURCE
    symboltable/SymbolObject.cpp
    symboltable/SymbolTable.cpp
    symboltable/SymbolTableScope.cpp
    symboltable/TypePosition.cpp
PARENT_SCOPE) 