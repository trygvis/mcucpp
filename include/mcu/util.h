#pragma once

#include <limits>
#include <type_traits>
#include <cstdint>

namespace mcu {

template<typename R = std::size_t, typename T, std::size_t N>
static inline constexpr
R SizeOfArray(const T(&array)[N])
{
    static_assert(std::numeric_limits<R>::max() >= N, "N does not fit in R");
    return static_cast<R>(N);
}

} // namespace mcu

namespace mcu {

/**
 * Template for selecting the smallest possible intX_t type that can hold Value.
 *
 * @tparam Value
 */
template<long long Value, class Enable = void>
class value_to_int_t;

template<long long Value>
class value_to_int_t<Value, typename std::enable_if<
    Value <= std::numeric_limits<int8_t>::max()>::type> {
public:
    typedef int8_t type;
    using fast_type = int_fast8_t;
    using least_type = int_least8_t;
};

template<long long Value>
class value_to_int_t<Value, typename std::enable_if<
    std::numeric_limits<int8_t>::max() < Value &&
    Value <= std::numeric_limits<int16_t>::max()>::type> {
public:
    using type = int16_t;
    using fast_type = int_fast16_t;
    using least_type = int_least16_t;
};

template<long long Value>
class value_to_int_t<Value, typename std::enable_if<
    std::numeric_limits<int16_t>::max() < Value &&
    Value <= std::numeric_limits<int32_t>::max()>::type> {
public:
    using type = int32_t;
    using fast_type = int_fast32_t;
    using least_type = int_least32_t;
};

template<long long Value>
class value_to_int_t<Value, typename std::enable_if<
    std::numeric_limits<int32_t>::max() < Value &&
    Value <= std::numeric_limits<int64_t>::max()>::type> {
public:
    using type = int64_t;
    using fast_type = int_fast64_t;
    using least_type = int_least64_t;
};

} // namespace mcu

namespace mcu {

/**
 * Template for selecting the smallest possible uintX_t type that can hold Value.
 *
 * @tparam Value
 */
template<unsigned long long Value, class Enable = void>
class value_to_uint_t;

template<unsigned long long Value>
class value_to_uint_t<Value, typename std::enable_if<
    Value <= std::numeric_limits<uint8_t>::max()>::type> {
public:
    using type = uint8_t;
    using fast_type = uint_fast8_t;
    using least_type = uint_least8_t;
};

template<unsigned long long Value>
class value_to_uint_t<Value, typename std::enable_if<
    std::numeric_limits<uint8_t>::max() < Value &&
    Value <= std::numeric_limits<uint16_t>::max()>::type> {
public:
    using type = uint16_t;
    using fast_type = uint_fast16_t;
    using least_type = uint_least16_t;
};

template<unsigned long long Value>
class value_to_uint_t<Value, typename std::enable_if<
    std::numeric_limits<uint16_t>::max() < Value &&
    Value <= std::numeric_limits<uint32_t>::max()>::type> {
public:
    using type = uint32_t;
    using fast_type = uint_fast32_t;
    using least_type = uint_least32_t;
};

template<unsigned long long Value>
class value_to_uint_t<Value, typename std::enable_if<
    std::numeric_limits<uint32_t>::max() < Value &&
    Value <= std::numeric_limits<uint64_t>::max()>::type> {
public:
    using type = uint64_t;
    using fast_type = uint_fast64_t;
    using least_type = uint_least64_t;
};

} // namespace mcu

namespace mcu {

template<unsigned long long Value, class Enable = void>
class bitmap_t;

template<unsigned long long Value>
class bitmap_t<Value, typename std::enable_if<Value <= 8>::type> {
public:
    using type = uint8_t;
    using fast_type = uint_fast8_t;
    using least_type = uint_least8_t;
};

template<unsigned long long Value>
class bitmap_t<Value, typename std::enable_if<8 < Value && Value <= 16>::type> {
public:
    using type = uint16_t;
    using fast_type = uint_fast16_t;
    using least_type = uint_least16_t;
};

template<unsigned long long Value>
class bitmap_t<Value, typename std::enable_if<16 < Value && Value <= 32>::type> {
public:
    using type = uint32_t;
    using fast_type = uint_fast32_t;
    using least_type = uint_least32_t;
};

template<unsigned long long Value>
class bitmap_t<Value, typename std::enable_if<32 < Value && Value <= 64>::type> {
public:
    using type = uint64_t;
    using fast_type = uint_fast64_t;
    using least_type = uint_least64_t;
};

} // namespace mcu
