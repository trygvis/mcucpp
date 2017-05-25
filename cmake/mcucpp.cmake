set(MCUCPP_PREFIX ${CMAKE_CURRENT_LIST_DIR}/../)
get_filename_component(MCUCPP_PREFIX ${MCUCPP_PREFIX} ABSOLUTE)

find_program(KCONFIG_PROGRAM NAMES kconfig)

function(_mcucpp_load_dotconfig TARGET)
  get_target_property(DOTCONFIG "${TARGET}" DOTCONFIG)

  file(STRINGS ${DOTCONFIG} dotconfig REGEX [^\"])
  foreach (C IN LISTS dotconfig)
    if ("${C}" MATCHES "([^=]*)=\"?([^\"]*)\"?")
      set(K ${CMAKE_MATCH_1})
      set(V ${CMAKE_MATCH_2})

      # message("dotconfig: ${K} -> ${V}")
      set("${K}" "${V}" PARENT_SCOPE)
    endif ()
  endforeach ()
endfunction()

function(mcucpp_configure_target)
  set(options)
  set(oneValueArgs TARGET DOTCONFIG)
  set(multiValueArgs)
  cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (NOT ARGS_TARGET)
    message(FATAL_ERROR "Missing required argument TARGET")
  endif ()
  set(T ${ARGS_TARGET})

  if (NOT ARGS_DOTCONFIG)
    set(DOTCONFIG "${PROJECT_SOURCE_DIR}/.config")
  else ()
    set(DOTCONFIG "${ARGS_DOTCONFIG}")
  endif ()

  get_filename_component(DOTCONFIG_DIR "${DOTCONFIG}" DIRECTORY)

  set_target_properties(${T} PROPERTIES DOTCONFIG ${DOTCONFIG})

  set(KCONFIG_CMAKE ${CMAKE_BINARY_DIR}/mcucpp/${T}-kconfig.cmake)

  if (NOT KCONFIG_PROGRAM)
    message("Could not find kconfig-frontend in PATH, won't create targets for launching kconfig.")
    message("This is not a problem unless you need to change the configuration. See the docs for more info: ${MCUCPP_PREFIX}/doc/kconfig.md")
  else ()
    get_filename_component(KCONFIG_DIR "${KCONFIG_PROGRAM}" DIRECTORY)

    if (WIN32)
      set(PATH "${KCONFIG_DIR};$ENV{PATH}")
    else ()
      set(PATH "${KCONFIG_DIR}:$ENV{PATH}")
    endif ()

    add_custom_target(${T}-kconfig
      DEPENDS "${DOTCONFIG}"
      BYPRODUCTS "${DOTCONFIG}"
      COMMAND ${CMAKE_COMMAND} -E env "PATH=${PATH}" kconfig mconf ${MCUCPP_PREFIX}/Kconfig
      COMMAND ${CMAKE_COMMAND} -E touch "${KCONFIG_CMAKE}"
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      USES_TERMINAL)
  endif ()

  file(WRITE "${KCONFIG_CMAKE}" "# Marker file.
# Touched by the $target-kconfig goal to get CMake to reload the configuration
")
  include(${KCONFIG_CMAKE})

endfunction()

macro(_mcucpp_append)
  foreach (item ${ARGN})
    set(item ${MCUCPP_PREFIX}/${item})

    if (item MATCHES "\\.h$")
      list(APPEND HEADERS ${item})
    elseif (item MATCHES "\\.c$" OR item MATCHES "\\.cpp$")
      list(APPEND SOURCES ${item})
    else ()
      list(APPEND INCLUDE_DIRECTORIES ${item})
    endif ()
  endforeach ()
endmacro()

function(mcucpp_process)

  set(options)
  set(oneValueArgs TARGET DEBUG)
  set(multiValueArgs)
  cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(INCLUDE_DIRECTORIES "")
  set(HEADERS "")
  set(SOURCES "")

  if (NOT ARGS_TARGET)
    message(FATAL_ERROR "Missing required argument TARGET")
  endif ()

  _mcucpp_load_dotconfig(${ARGS_TARGET})

  _mcucpp_append(
    include

    include/mcu/nonew/function.h
    include/mcu/nonew/queue.h

    include/mcu/io/output_stream.h
    src/io/output_stream.cpp

    include/mcu/stm32cube/debug.h

    include/mcu/stm32cube/uart.h
    src/stm32cube/uart.cpp
  )

  if (CONFIG_TINYPRINTF)
    _mcucpp_append(
      thirdparty/tinyprintf
      thirdparty/tinyprintf/tinyprintf.h
      thirdparty/tinyprintf/tinyprintf.c)
  endif ()

  if (CONFIG_TINYPRINTF_PRINTF)
    _mcucpp_append(src/generic/tinyprintf-printf.cpp)
  endif ()

  if (CONFIG_TINYPRINTF_SNPRINTF)
    _mcucpp_append(src/generic/tinyprintf-snprintf.cpp)
  endif ()

  if (CONFIG_SEMIHOSTING)
    _mcucpp_append(
      include/mcu/arm/semihosting.h
      src/arm/semihosting.cpp)
  endif ()

  if (CONFIG_SEMIHOSTING_PUTCHAR)
    _mcucpp_append(src/arm/semihosting-putchar.cpp)
  endif ()

  if (CONFIG_SEMIHOSTING_PUTS)
    _mcucpp_append(src/arm/semihosting-puts.cpp)
  endif ()

  # Stdio settings

  if (CONFIG_STDIO_TARGET_SEMIHOSTING)
    _mcucpp_append(
      src/arm/semihosting-stdout.cpp)
  endif ()

  if (CONFIG_STDIO_TARGET_STM32CUBE_UART)
    _mcucpp_append(
      src/generic/putchar.cpp
      src/generic/puts.cpp
      src/stm32cube/stdout-impl.cpp)

    set_source_files_properties(
      ${MCUCPP_PREFIX}/src/stm32cube/stdout-impl.cpp
      PROPERTIES COMPILE_DEFINITIONS CONFIG_STDIO_TARGET_STM32CUBE_UART_PORT=${CONFIG_STDIO_TARGET_STM32CUBE_UART_PORT})
  endif ()

  # Debugging

  if (ARGS_DEBUG)
    message("Include directories")
    foreach (D IN LISTS INCLUDE_DIRECTORIES)
      message(" - ${D}")
    endforeach ()

    message("Header files")
    foreach (F IN LISTS HEADERS)
      message(" - ${F}")
    endforeach ()

    message("Source files")
    foreach (F IN LISTS SOURCES)
      message(" - ${F}")
    endforeach ()
  endif ()

  if (ARGS_TARGET)
    target_include_directories(${ARGS_TARGET} PUBLIC ${INCLUDE_DIRECTORIES})
    target_sources(${ARGS_TARGET} PUBLIC ${SOURCES})
  endif ()

endfunction()
