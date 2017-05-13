#include <cstdio>
#include <cstdarg>

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

    // Remove the last \n so we can use puts() (which add a \n).
    if (buf[size - 1] == '\n') {
        buf[size - 1] = 0;
    }

    puts(buf);

    return 0;
}
