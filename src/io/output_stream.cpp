#include "mcu/io/output_stream.h"

#include <cstdio>
#include <mcu/util.h>
#include <cstdarg>
#include <tinyprintf.h>

namespace mcu {
namespace io {

size_t formatted_output_stream::println(const char *format, ...) {
    char buffer[100];

    va_list args;
    va_start(args, format);
    int count = tfp_vsnprintf(buffer, SizeOfArray(buffer), format, args);
    va_end(args);

    auto written = write(reinterpret_cast<uint8_t *>(buffer), count);
    if (written == count) {
        uint8_t c = '\n';
        written += write(&c, 1);
    }
    return written;
//    return 0;
}

} // namespace io
} // namespace mcu
