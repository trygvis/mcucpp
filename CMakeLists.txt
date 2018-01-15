cmake_minimum_required(VERSION 3.6)

project(mcucpp C CXX ASM)

include_directories(include)
add_executable(tests
  test/tests.cpp
  test/catch.hpp
  test/test-utils.h

  src/experimental.cpp
  test/experimental-test.cpp

  include/mcu/nonew/function.h
  test/function-test.cpp

  include/mcu/nonew/queue.h
  test/queue-test.cpp

  include/mcu/util.h
  test/util-value_to_int_t-test.cpp

  include/mcu/array_view.h
  test/string_view-test.cpp
  )

if (${CMAKE_COMPILER_IS_GNUCXX})
  target_compile_options(tests PUBLIC -Wall -Wextra -Werror --pedantic)
endif ()

find_package(Doxygen
  REQUIRED dot
  OPTIONAL_COMPONENTS mscgen dia)

if (DOXYGEN_FOUND)
  doxygen_add_docs(
    doxygen
    src include
    COMMENT "Generate man pages"
  )
endif ()
