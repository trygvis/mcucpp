#pragma once

#include <cstdint>
#include <cstddef>

namespace mcu {
namespace io {
namespace internal {

/**
 * Write character to stdout
 *
 * @param chr
 * @return Returns true if the character was successfully written.
 */
size_t stdout_putchar(char chr);

/**
 * Writes a null-terminated string to stdout
 *
 * @param chr
 * @return Returns the number of characters written.
 */
size_t stdout_puts(const char *str);

/**
 * Writes a string of the specified length to stdout
 *
 * @param chr
 * @return Returns the number of bytes written.
 */
size_t stdout_write(const uint8_t *str, size_t size);

} // namespace internal
} // namespace io
} // namespace mcu
