cmake_minimum_required(VERSION 3.8)

project(src)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(SOURCE_FILES
        src/calc.c
        ${CMAKE_CURRENT_BINARY_DIR}/calcScanner.c
        ${CMAKE_CURRENT_BINARY_DIR}/calcParser.c
        )

include_directories(AFTER src ${CMAKE_CURRENT_BINARY_DIR})

find_package(BISON)
find_package(FLEX)

BISON_TARGET(calcParser src/calc.y ${CMAKE_CURRENT_BINARY_DIR}/calcParser.c VERBOSE)
FLEX_TARGET(calcScanner src/calc.l ${CMAKE_CURRENT_BINARY_DIR}/calcScanner.c)

ADD_FLEX_BISON_DEPENDENCY(calcScanner calcParser)

add_executable(
        calc
        ${SOURCE_FILES}
        ${BISON_calcParser_OUTPUTS}
        ${FLEX_calcScanner_OUTPUTS}
)