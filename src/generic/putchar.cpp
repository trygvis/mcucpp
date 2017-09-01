#include <mcu/io/internal.h>

using namespace mcu::io::internal;

extern "C"
__attribute__((used))
int putchar(char chr)
{
    return stdout_putchar(chr);
}
