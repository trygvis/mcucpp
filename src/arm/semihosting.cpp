#include <mcu/arm/semihosting.h>

namespace semihosting {

volatile bool _enabled = false;

void disable()
{
    _enabled = false;
}

bool enabled()
{
    return _enabled;
}

void enable()
{
    _enabled = true;
}

uint32_t send_command(enum SemihostingCmd command, void const *message)
{
    if (!_enabled) {
        return UINT32_MAX;
    }

    auto c = static_cast<int>(command);
    uint32_t r;

    __asm volatile (
    "mov r0, %[cmd];"
        "mov r1, %[msg];"
        "bkpt #0xAB;"
        "mov %[ret], r0;"
    : [ret] "=r"(r)
    : [cmd] "r"(c), [msg] "r"(message)
    : "r0", "r1", "memory"
    );

    return r;
}

} // namespace semihosting
