cmake_minimum_required(VERSION 3.6)

set(MCU_CHIP stm32f103c8)
include(../thirdparty/mcu.cmake/mcu.cmake)

project(mcucpp-examples C CXX ASM)

list(APPEND SHARED_SOURCES
    ../thirdparty/mcu.cmake/stm32f103/src/init_high.cpp
    ../thirdparty/mcu.cmake/stm32f103/src/init_low.s
    ../thirdparty/mcu.cmake/stm32f103/src/default_handler.cpp

    ../include/mcu/arm/semihosting.h
    ../src/arm/semihosting.cpp
    ../src/arm/semihosting-puts.cpp
    ../src/arm/semihosting-putchar.cpp

    ../thirdparty/tinyprintf/tinyprintf.c
    ../thirdparty/tinyprintf/tinyprintf.h
    ../src/generic/tinyprintf-printf.cpp
    ../src/generic/tinyprintf-snprintf.cpp

    ../thirdparty/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/core_cm3.h)

list(APPEND SHARED_INCLUDES
    ../include
    ../thirdparty/mcu.cmake/stm32f103/include
    ../thirdparty/tinyprintf
    ../thirdparty/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport
    ../thirdparty/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x)

list(APPEND SHARED_LIBRARIES gcc)

add_executable(hello-world
    hello-world/main.cpp
    ${SHARED_SOURCES})
mcu_add_executable(TARGET hello-world)
target_include_directories(hello-world PUBLIC ${SHARED_INCLUDES})
target_link_libraries(hello-world PUBLIC ${SHARED_LIBRARIES})

add_executable(interrupt-handling
    interrupt-handling/main.cpp
    ${SHARED_SOURCES})
mcu_add_executable(TARGET interrupt-handling)
target_include_directories(interrupt-handling PUBLIC ${SHARED_INCLUDES})
target_link_libraries(interrupt-handling PUBLIC ${SHARED_LIBRARIES})

# For CLion
include_directories(interrupt-handling ../thirdparty/mcu.cmake)
include_directories(interrupt-handling ../thirdparty/STM32F10x_StdPeriph_Lib_V3.5.0)
include_directories(interrupt-handling ../src ../include)
