#pragma once

#include "stm32f1xx_hal_uart.h"
#include "mcu/io/output_stream.h"

namespace mcu {
namespace stm32cubemx {
namespace uart {

class uart_port : public mcu::io::output_stream {
public:
    explicit uart_port(UART_HandleTypeDef *handle) noexcept;

    void enable();

    void disable();

    using mcu::io::output_stream::write;
    size_t write(const uint8_t *data, size_t size) override;

private:
    UART_HandleTypeDef *handle_;
};

} // namespace uart
} // namespace stm32cubemx
} // namespace mcu
