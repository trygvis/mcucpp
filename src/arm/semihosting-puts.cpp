#include <mcu/arm/semihosting.h>
#include <cstdio>

using namespace semihosting;

extern "C"
__attribute__((used))
int puts(const char *s)
{
    send_command(SemihostingCmd::SYS_WRITE0, (void *) s);
    char eol = '\n';
    send_command(SemihostingCmd::SYS_WRITEC, &eol);
    return 1;
}
