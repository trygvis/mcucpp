cmake_minimum_required(VERSION 3.6)

project(mcu.cmake-test C CXX ASM)

include_directories(src embxx)
add_executable(tests
        test/tests.cpp
        test/catch.hpp

        src/mcu/nonew/function.h
        test/function-test.cpp

        src/mcu/nonew/queue.h
        test/queue-test.cpp
        )
