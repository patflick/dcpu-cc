cmake_minimum_required(VERSION 2.8.5)

# Set header .h files
SET (NODES_EXPR_HEADERS
    astnodes/expression/AddressOfOperator.h
    astnodes/expression/ArrayAccessOperator.h
    astnodes/expression/AssignmentOperator.h
    astnodes/expression/BinaryOperator.h
    astnodes/expression/ChainExpressions.h
    astnodes/expression/ConditionalOperator.h
    astnodes/expression/DerefOperator.h
    astnodes/expression/ExplicitCastOperator.h
    astnodes/expression/Expression.h
    astnodes/expression/Expressions.h
    astnodes/expression/Identifier.h
    astnodes/expression/MethodCall.h
    astnodes/expression/PostIncDec.h
    astnodes/expression/PreIncDec.h
    astnodes/expression/SizeOfOperator.h
    astnodes/expression/StructureResolutionOperator.h
    astnodes/expression/TypeConversionOperator.h
    astnodes/expression/UnaryOperator.h
    astnodes/expression/literals/CharacterLiteral.h
    astnodes/expression/literals/DoubleLiteral.h
    astnodes/expression/literals/FloatLiteral.h
    astnodes/expression/literals/LongDoubleLiteral.h
    astnodes/expression/literals/SignedIntLiteral.h
    astnodes/expression/literals/SignedLongLiteral.h
    astnodes/expression/literals/StringLiteral.h
    astnodes/expression/literals/UnsignedIntLiteral.h
    astnodes/expression/literals/UnsignedLongLiteral.h
PARENT_SCOPE)

# Set source .cpp files
set (NODES_EXPR_SOURCE
    astnodes/expression/AddressOfOperator.cpp
    astnodes/expression/ArrayAccessOperator.cpp
    astnodes/expression/AssignmentOperator.cpp
    astnodes/expression/BinaryOperator.cpp
    astnodes/expression/ChainExpressions.cpp
    astnodes/expression/ConditionalOperator.cpp
    astnodes/expression/DerefOperator.cpp
    astnodes/expression/ExplicitCastOperator.cpp
    astnodes/expression/Expression.cpp
    astnodes/expression/Identifier.cpp
    astnodes/expression/MethodCall.cpp
    astnodes/expression/PostIncDec.cpp
    astnodes/expression/PreIncDec.cpp
    astnodes/expression/SizeOfOperator.cpp
    astnodes/expression/StructureResolutionOperator.cpp
    astnodes/expression/TypeConversionOperator.cpp
    astnodes/expression/UnaryOperator.cpp
    astnodes/expression/literals/CharacterLiteral.cpp
    astnodes/expression/literals/DoubleLiteral.cpp
    astnodes/expression/literals/FloatLiteral.cpp
    astnodes/expression/literals/LongDoubleLiteral.cpp
    astnodes/expression/literals/SignedIntLiteral.cpp
    astnodes/expression/literals/SignedLongLiteral.cpp
    astnodes/expression/literals/StringLiteral.cpp
    astnodes/expression/literals/UnsignedIntLiteral.cpp
    astnodes/expression/literals/UnsignedLongLiteral.cpp
PARENT_SCOPE) 

