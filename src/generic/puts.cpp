#include <mcu/io/internal.h>

using namespace mcu::io::internal;

extern "C"
__attribute__((used))
int puts(const char *s)
{
    stdout_puts(s);
}
