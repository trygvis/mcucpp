#pragma once

#include "mcu/nonew/queue.h"
#include "mcu/io/output_stream.h"

namespace mcu {
namespace stm32cubemx {
namespace debug {

template<size_t BufferSize>
class dbg : public mcu::io::formatted_output_stream {

public:
    explicit dbg(mcu::io::output_stream &output) noexcept;

    size_t write(const uint8_t *data, size_t size) override;

protected:
    mcu::io::output_stream &output_;
    mcu::nonew::queue<char, BufferSize> q;
};

template<size_t BufferSize>
dbg<BufferSize>::dbg(mcu::io::output_stream &output) noexcept : output_(output) {
    // TODO: register a callback with the UART so it can notify when the buffer is empty
}

template<size_t BufferSize>
size_t dbg<BufferSize>::write(const uint8_t *data, size_t size) {
    size_t written = output_.write(data, size);

    size -= written;
    if (size == 0) {
        return written;
    }

    while (!q.is_full()) {
        q.push_back(data[written++]);
    }

    return written;
}

} // namespace debug
} // namespace stm32cubemx
} // namespace mcu
