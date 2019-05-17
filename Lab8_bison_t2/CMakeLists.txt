cmake_minimum_required(VERSION 3.8)

project(ciProlog)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES
        src/ciProlog.c
        ${CMAKE_CURRENT_BINARY_DIR}/ciPrologScanner.c
        ${CMAKE_CURRENT_BINARY_DIR}/ciPrologParser.c
        )

include_directories(AFTER src ${CMAKE_CURRENT_BINARY_DIR})

find_package(BISON)
find_package(FLEX)

BISON_TARGET(ciPrologParser src/ciProlog.y ${CMAKE_CURRENT_BINARY_DIR}/ciPrologParser.c VERBOSE)
FLEX_TARGET(ciPrologScanner src/ciProlog.l  ${CMAKE_CURRENT_BINARY_DIR}/ciPrologScanner.c)

ADD_FLEX_BISON_DEPENDENCY(ciPrologScanner ciPrologParser)

add_executable(
        ciprolog
        ${SOURCE_FILES}
        ${BISON_calcParser_OUTPUTS}
        ${FLEX_calcScanner_OUTPUTS}
)