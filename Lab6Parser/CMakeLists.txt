cmake_minimum_required(VERSION 3.8)
project(parser)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/parser.c
        src/eval.c
        src/scanner_ad_hoc.c src/parser.c src/main.c)

include_directories(AFTER src)

add_executable(parser ${SOURCE_FILES} src/main.c)