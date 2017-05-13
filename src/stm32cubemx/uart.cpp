#include <cstring>
#include "stm32f1xx_hal_dma.h"
#include "mcu/stm32cubemx/uart.h"

namespace mcu {
namespace stm32cubemx {
namespace uart {

uart_port::uart_port(UART_HandleTypeDef *handle) noexcept : handle_(handle) {
}

void uart_port::enable() {
}

void uart_port::disable() {
}

size_t uart_port::write(const uint8_t *data, size_t size) {
    auto *d = const_cast<uint8_t *>(data);
    HAL_UART_Transmit(handle_, d, size, 1000);
    return size;
}

} // namespace uart
} // namespace stm32cubemx
} // namespace mcu
