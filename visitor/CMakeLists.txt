cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)

# Set header .h files
SET (VISITOR_HEADER
    visitor/Visitor.h
    visitor/CheckTypedefVisitor.h
    visitor/ConstExprEvalVisitor.h
    visitor/EmptyVisitor.h
    visitor/GotoResolvalVisitor.h
    visitor/PrintAstVisitor.h
    visitor/SemanticCheckVisitor.h
PARENT_SCOPE)

# Set source .cpp files
set (VISITOR_SOURCE
    visitor/CheckTypedefVisitor.cpp
    visitor/ConstExprEvalVisitor.cpp
    visitor/EmptyVisitor.cpp
    visitor/GotoResolvalVisitor.cpp
    visitor/PrintAstVisitor.cpp
    visitor/SemanticCheckVisitor.cpp
PARENT_SCOPE) 