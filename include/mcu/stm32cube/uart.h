#pragma once

#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_uart.h"
#include "mcu/io/output_stream.h"

namespace mcu {
namespace stm32cube {
namespace uart {

class uart_port : public mcu::io::output_stream {
public:
    explicit uart_port(UART_HandleTypeDef *handle) noexcept;

    void enable();

    void disable();

    using mcu::io::output_stream::write;
    size_t write(const uint8_t *data, size_t size) override;

    __always_inline
    bool tx_busy() {
        return HAL_UART_GetState(handle_) & HAL_UART_STATE_BUSY_TX;
    }

private:
    UART_HandleTypeDef *handle_;
};

} // namespace uart
} // namespace stm32cube
} // namespace mcu
