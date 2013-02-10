cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)

# Set header .h files
SET (CODEGEN_HEADER
    codegen/Assembler.h
    codegen/DirectCodeGenVisitor.h
    codegen/ValuePosition.h
    codegen/typeimpl/GetTypeImplVisitor.h
    codegen/typeimpl/TypeImplementation.h
    codegen/typeimpl/TypeConversions.h
    codegen/typeimpl/TypeSizes.h
    codegen/typeimpl/Int16.h
    codegen/typeimpl/SignedInt16.h
    codegen/typeimpl/UnsignedInt16.h
PARENT_SCOPE)

# Set source .cpp files
set (CODEGEN_SOURCE
    codegen/Assembler.cpp
    codegen/DirectCodeGenVisitor.cpp
    codegen/ValuePosition.cpp
    codegen/typeimpl/GetTypeImplVisitor.cpp
    codegen/typeimpl/Int16.cpp
    codegen/typeimpl/TypeConversions.cpp
    codegen/typeimpl/SignedInt16.cpp
    codegen/typeimpl/UnsignedInt16.cpp
PARENT_SCOPE) 