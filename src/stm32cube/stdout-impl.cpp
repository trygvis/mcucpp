#include <mcu/io/internal.h>

#include <stm32f1xx_hal_dma.h>
#include <stm32f1xx_hal_uart.h>
#include <cstring>
#include <algorithm>

#ifndef CONFIG_STDIO_TARGET_STM32CUBE_UART_PORT
#error "Invalid usage, this file can't be compiled without defining CONFIG_STDIO_TARGET_STM32CUBE_UART_PORT."
#endif

#define handle CONFIG_STDIO_TARGET_STM32CUBE_UART_PORT

namespace mcu {
namespace io {
namespace internal {

extern "C"
UART_HandleTypeDef handle;

size_t stdout_putchar(char chr)
{
    auto data = static_cast<uint8_t>(chr);
    HAL_UART_Transmit(&handle, &data, 1, 100);

    return 1;
}

size_t stdout_puts(const char *str)
{
    size_t size = strlen(str);
    auto written = stdout_write(reinterpret_cast<const uint8_t *>(str), size);

    if (written != size) {
        return written;
    }

    uint8_t eol = '\n';
    return written + stdout_write(&eol, 1);
}

size_t stdout_write(const uint8_t *str, size_t size)
{
    for (size_t i = 0; i < size; i += std::numeric_limits<uint16_t>::max()) {
        uint16_t packet = size > std::numeric_limits<uint16_t>::max() ?
                          std::numeric_limits<uint16_t>::max() :
                          static_cast<uint16_t>(size);

        HAL_UART_Transmit(&handle, const_cast<uint8_t *>(str), packet, 100);
    }

    return size;
}

} // namespace internal
} // namespace io
} // namespace mcu
