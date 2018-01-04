#include <mcu/io/output_stream.h>
#include <mcu/util.h>

#include <cstdio>
#include <cstdarg>

#include <mcu/config.h>

#if CONFIG_TINYPRINTF
#include <tinyprintf.h>
#else
#error "Missing tinyprintf implementation"
#endif

namespace mcu {
namespace io {

size_t formatted_output_stream::print(const char *format, ...)
{
    char buffer[100];

    va_list args;
    va_start(args, format);
    int count = tfp_vsnprintf(buffer, SizeOfArray(buffer), format, args);
    va_end(args);

    return write(reinterpret_cast<uint8_t *>(buffer), count);
}

size_t formatted_output_stream::println(const char *format, ...)
{
    char buffer[100];

    va_list args;
    va_start(args, format);
    int count = tfp_vsnprintf(buffer, SizeOfArray(buffer), format, args);
    va_end(args);

    auto written = write(reinterpret_cast<uint8_t *>(buffer), count);
    if (written == static_cast<size_t>(count)) {
        uint8_t c = '\n';
        written += write(&c, 1);
    }
    return written;
}

size_t formatted_output_stream::println() {
    uint8_t c = '\n';
    return write(&c, 1);
}

} // namespace io
} // namespace mcu
