cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)

# Set header .h files
SET (NODES_DECL_HEADERS
    astnodes/declaration/ArrayDeclarator.h
    astnodes/declaration/Declaration.h
    astnodes/declaration/Declarations.h
    astnodes/declaration/DeclarationSpecifiers.h
    astnodes/declaration/Declarator.h
    astnodes/declaration/Declarators.h
    astnodes/declaration/Enumerator.h
    astnodes/declaration/Enumerators.h
    astnodes/declaration/EnumSpecifier.h
    astnodes/declaration/ExternalDeclaration.h
    astnodes/declaration/ExternalDeclarations.h
    astnodes/declaration/FunctionDeclarator.h
    astnodes/declaration/IdentifierDeclarator.h
    astnodes/declaration/NoIdentifierDeclarator.h
    astnodes/declaration/ParameterDeclarations.h
    astnodes/declaration/Pointer.h
    astnodes/declaration/Pointers.h
    astnodes/declaration/StorageSpecifier.h
    astnodes/declaration/StructUnionSpecifier.h
    astnodes/declaration/TypeBaseSpecifier.h
    astnodes/declaration/TypeName.h
    astnodes/declaration/TypeNameSpecifier.h
    astnodes/declaration/TypeQualifier.h
    astnodes/declaration/TypeQualifiers.h
    astnodes/declaration/TypeSpecifier.h
PARENT_SCOPE)

# Set source .cpp files
set (NODES_DECL_SOURCE
    astnodes/declaration/ArrayDeclarator.cpp
    astnodes/declaration/Declaration.cpp
    astnodes/declaration/Declarator.cpp
    astnodes/declaration/Enumerator.cpp
    astnodes/declaration/EnumSpecifier.cpp
    astnodes/declaration/FunctionDeclarator.cpp
    astnodes/declaration/IdentifierDeclarator.cpp
    astnodes/declaration/NoIdentifierDeclarator.cpp
    astnodes/declaration/Pointer.cpp
    astnodes/declaration/StorageSpecifier.cpp
    astnodes/declaration/StructUnionSpecifier.cpp
    astnodes/declaration/TypeBaseSpecifier.cpp
    astnodes/declaration/TypeName.cpp
    astnodes/declaration/TypeNameSpecifier.cpp
    astnodes/declaration/TypeQualifier.cpp
    astnodes/declaration/TypeSpecifier.cpp
PARENT_SCOPE) 

