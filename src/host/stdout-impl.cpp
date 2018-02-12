#include <mcu/config.h>
#include <mcu/io/internal.h>
#include <cstdio>

#if CONFIG_CHIP_FAMILY_HOST

namespace mcu {
namespace io {
namespace internal {

void stdout_init()
{
}

size_t stdout_putchar(char chr)
{
    std::putchar(chr);
}

size_t stdout_puts(const char *str)
{
    std::puts(str);
}

size_t stdout_write(const uint8_t *str, size_t size)
{
    std::fwrite(str, size, 1, stdout);
    std::fflush(stdout);
}

} // namespace internal
} // namespace io
} // namespace mcu

#endif // CHIP_FAMILY_HOST
