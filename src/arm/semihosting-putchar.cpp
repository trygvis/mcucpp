#include <mcu/arm/semihosting.h>

using namespace semihosting;

extern "C"
__attribute__((used))
int putchar(char c)
{
    send_command(SemihostingCmd::SYS_WRITEC, &c);
    return 1;
}
