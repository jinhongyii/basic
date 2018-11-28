cmake_minimum_required(VERSION 3.12)
project(BASIC)

set(CMAKE_CXX_STANDARD 14)

add_executable(code Basic.cpp evalstate.cpp exp.cpp parser.cpp program.cpp statement.cpp
        error.cpp tokenscanner.cpp simpio.cpp strlib.cpp calculate.cpp)
