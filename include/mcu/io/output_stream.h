#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace mcu {
namespace io {

class output_stream {
public:
    size_t write(char c) {
        return write(reinterpret_cast<uint8_t *>(&c), 1);
    }

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
    size_t print(const char *format, ...);
    size_t println(const char *format, ...);
    size_t println();

protected:
};


} // namespace io
} // namespace mcu
