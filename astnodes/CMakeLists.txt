cmake_minimum_required(VERSION 2.8.5)
project(dtcc2tests)

add_subdirectory(declaration)
add_subdirectory(expression)
add_subdirectory(statement)
add_subdirectory(extensions)


# Set header .h files
SET (NODES_HEADERS
    astnodes/Node.h
    astnodes/FunctionDefinition.h
    astnodes/Program.h
    ${NODES_DECL_HEADERS}
    ${NODES_STMT_HEADERS}
    ${NODES_EXPR_HEADERS}
    ${NODES_EXT_HEADERS}
PARENT_SCOPE)

# Set source .cpp files
set (NODES_SOURCE
    astnodes/FunctionDefinition.cpp
    astnodes/Program.cpp
    ${NODES_DECL_SOURCE}
    ${NODES_STMT_SOURCE}
    ${NODES_EXPR_SOURCE}
    ${NODES_EXT_SOURCE}
PARENT_SCOPE)

