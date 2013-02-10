cmake_minimum_required(VERSION 2.8.5)
project(dcpucc-errgen)

SET (ERRGEN_BIN_PATH
    ${CMAKE_CURRENT_BINARY_DIR}
    PARENT_SCOPE)

add_executable(dcpucc-errgen
    main.cpp
)
