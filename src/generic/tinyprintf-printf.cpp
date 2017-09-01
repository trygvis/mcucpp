#include <cstdio>
#include <cstdarg>
#include <mcu/io/internal.h>

#define TINYPRINTF_DEFINE_TFP_PRINTF 0
#define TINYPRINTF_OVERRIDE_LIBC 0
#include "tinyprintf.h"

extern "C"
int printf(const char *format, ...) {
    const size_t buffer_size = 1000;
    char buf[buffer_size];

    va_list args;
    va_start(args, format);
    int size = tfp_vsnprintf(buf, buffer_size, format, args);
    va_end(args);

    mcu::io::internal::stdout_write(
        reinterpret_cast<uint8_t *>(&buf[0]),
        static_cast<size_t>(size + 1));

    return size;
}
