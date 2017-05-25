#include <mcu/io/internal.h>

using namespace mcu::io::internal;

extern "C"
__attribute__((used))
int putchar(char chr)
{
    stdout_putchar(chr);
}
