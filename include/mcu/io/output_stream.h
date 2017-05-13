#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace mcu {
namespace io {

class output_stream {
public:
    size_t write(const char *string) {
        size_t size = strlen(string);
        auto *s1 = const_cast<char *>(string);
        auto *s2 = reinterpret_cast<uint8_t *>(s1);
        return write(s2, size);
    };

    virtual size_t write(const uint8_t *data, size_t size) = 0;
};

class formatted_output_stream : public output_stream {
public:
    size_t println(const char *format, ...);

protected:
};


} // namespace io
} // namespace mcu
