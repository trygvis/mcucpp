cmake_minimum_required(VERSION 3.6)

project(mcucpp C CXX ASM)

include_directories(include)
add_executable(tests
    test/tests.cpp
    test/catch.hpp

    include/mcu/nonew/function.h
    test/function-test.cpp

    include/mcu/nonew/queue.h
    test/queue-test.cpp)
