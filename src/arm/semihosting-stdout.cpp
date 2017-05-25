#include <mcu/io/internal.h>
#include <mcu/arm/semihosting.h>

namespace mcu {
namespace io {
namespace internal {

using namespace semihosting;

bool stdout_putchar(char chr) {
    send_command(SemihostingCmd::SYS_WRITEC, &chr);

    return true;
}

bool stdout_puts(const char *str) {
    send_command(SemihostingCmd::SYS_WRITE0, (void *) str);
    char eol = '\n';
    send_command(SemihostingCmd::SYS_WRITEC, &eol);
    return true;
}

bool stdout_puts(const uint8_t *str, size_t size) {

    // There is no "write binary to debug channel" (only write char and write null-terminated strings) so this is a
    // a naive implementation that just writes a single byte at the time.

    // This is going to be very slow. It can be optimized
    for (size_t i = 0; i < size; i++) {
        send_command(SemihostingCmd::SYS_WRITEC, static_cast<void const *>(&str[i]));
    }

    return true;
}

} // namespace internal
} // namespace io
} // namespace mcu
