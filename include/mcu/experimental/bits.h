#pragma once

namespace mcu {
namespace bits {

template<typename Value, typename Bit>
static inline
bool is_set(Value value, Bit bit)
{

    auto mask = 1 << static_cast<int>(bit);

    return value & mask;
}

template<typename Value, typename Bit>
static inline
Value set_bit(Value value, Bit bit)
{

    auto mask = 1 << static_cast<int>(bit);

    return value | mask;
}

template<typename Value, typename Bit>
constexpr static inline
Value mask(Bit bit)
{
    auto msk = 1 << static_cast<int>(bit);

    return Value(msk);
}

template<typename Value, typename Bit, typename... Bits>
constexpr static inline
Value mask(Bit bit, Bits... rest)
{
    auto msk = 1 << static_cast<int>(bit);

    return Value(msk) | mask<Value>(rest...);
}

template<typename Value, typename Bit>
static inline
Value clear_bit(Value value, Bit bit)
{

    Value mask = 1 << static_cast<int>(bit);

    return value & ~mask;
}

} // namespace bits
} // namespace mcu
