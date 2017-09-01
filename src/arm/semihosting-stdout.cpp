#include <mcu/io/internal.h>
#include <mcu/arm/semihosting.h>
#include <mcu/config.h>
#include <cstring>

#if CONFIG_SEMIHOSTING

#include <stm32f1xx.h>

#endif

namespace mcu {
namespace io {
namespace internal {

using semihosting::send_command;
using semihosting::SemihostingCmd;

void stdout_init()
{
    bool debugger_connected;

#if CONFIG_SEMIHOSTING
    debugger_connected = (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk) != 0;
#else
    debugger_connected = false;
#endif

    if (debugger_connected) {
        semihosting::enable();
    } else {
        semihosting::disable();
    }
}

size_t stdout_putchar(char chr)
{
    send_command(SemihostingCmd::SYS_WRITEC, &chr);

    return 1;
}

size_t stdout_puts(const char *str)
{
    size_t len = strlen(str);
    send_command(SemihostingCmd::SYS_WRITE0, (void *) str);
    char eol = '\n';
    send_command(SemihostingCmd::SYS_WRITEC, &eol);
    return len;
}

size_t stdout_write(const uint8_t *const str, size_t size)
{
    // Write out all null-terminated strings we can find with SYS_WRITE0 and then switch to writing all the remaining
    // characters one by one.
    size_t done = 0;
    for (size_t i = 0; i < size; i++) {
        if (str[i] == '\0') {
            send_command(SemihostingCmd::SYS_WRITE0, &str[done]);
            done = i;
        }
    }

    for (size_t i = done; i < size; i++) {
        send_command(SemihostingCmd::SYS_WRITEC, &str[i]);
    }

    return size;
}

} // namespace internal
} // namespace io
} // namespace mcu
