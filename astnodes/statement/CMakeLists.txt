cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)

# Set header .h files
SET (NODES_STMT_HEADERS
    astnodes/statement/BlockStatement.h
    astnodes/statement/BreakStatement.h
    astnodes/statement/CaseStatement.h
    astnodes/statement/ContinueStatement.h
    astnodes/statement/DefaultStatement.h
    astnodes/statement/DoWhileStatement.h
    astnodes/statement/EmptyStatement.h
    astnodes/statement/ExpressionStatement.h
    astnodes/statement/ForStatement.h
    astnodes/statement/GotoStatement.h
    astnodes/statement/IfStatement.h
    astnodes/statement/LabelStatement.h
    astnodes/statement/ReturnStatement.h
    astnodes/statement/Statement.h
    astnodes/statement/Statements.h
    astnodes/statement/SwitchStatement.h
    astnodes/statement/WhileStatement.h
PARENT_SCOPE)

# Set source .cpp files
set (NODES_STMT_SOURCE
    astnodes/statement/BlockStatement.cpp
    astnodes/statement/BreakStatement.cpp
    astnodes/statement/CaseStatement.cpp
    astnodes/statement/ContinueStatement.cpp
    astnodes/statement/DefaultStatement.cpp
    astnodes/statement/DoWhileStatement.cpp
    astnodes/statement/EmptyStatement.cpp
    astnodes/statement/ExpressionStatement.cpp
    astnodes/statement/ForStatement.cpp
    astnodes/statement/GotoStatement.cpp
    astnodes/statement/IfStatement.cpp
    astnodes/statement/LabelStatement.cpp
    astnodes/statement/ReturnStatement.cpp
    astnodes/statement/Statement.cpp
    astnodes/statement/SwitchStatement.cpp
    astnodes/statement/WhileStatement.cpp
PARENT_SCOPE) 

