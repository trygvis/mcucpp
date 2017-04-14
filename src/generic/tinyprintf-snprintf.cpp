#include <cstdio>
#include <cstdarg>

#define TINYPRINTF_DEFINE_TFP_PRINTF 0
#define TINYPRINTF_OVERRIDE_LIBC 0
#include "tinyprintf.h"

extern "C"
int snprintf(char *str, size_t size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int count = tfp_vsnprintf(str, size, format, args);
    va_end(args);

    return count;
}
