#pragma once

namespace mcu {
namespace bits {

template<typename Value, typename Bit>
static inline
bool is_set(Value value, Bit bit) {

    auto mask = 1 << static_cast<int>(bit);

    return value & mask;
}

template<typename Value, typename Bit>
static inline
Value set_bit(Value value, Bit bit) {

    auto mask = 1 << static_cast<int>(bit);

    return value | mask;
}

template<typename Value, typename Bit>
static inline
Value clear_bit(Value value, Bit bit) {

    Value mask = 1 << static_cast<int>(bit);

    return value & ~mask;
}

} // namespace bits
} // namespace mcu
