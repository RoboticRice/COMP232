cmake_minimum_required(VERSION 3.8)
project(flex_t1)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(C_SOURCE_FILES src/flex_t1.c)

set(FLEX_SOURCE_FILES src/flex_t1.l)

include_directories(AFTER src)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(
        MyParser
        src/dummy.y
        ${CMAKE_CURRENT_BINARY_DIR}/parser.c
)

FLEX_TARGET(
        MyScanner
        ${FLEX_SOURCE_FILES}
        ${CMAKE_CURRENT_BINARY_DIR}/lexer.c
)

ADD_FLEX_BISON_DEPENDENCY(
        MyScanner
        MyParser
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(
        flex_t1
        ${C_SOURCE_FILES}
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
