#include "mcu/util.h"

#include "catch.hpp"

using std::is_same;
using mcu::value_to_int_t;
using mcu::value_to_uint_t;

TEST_CASE("value_to_int_t")
{
    static_assert(is_same<value_to_int_t<10>::type, int8_t>::value, "");
    static_assert(is_same<value_to_int_t<127>::type, int8_t>::value, "");
    static_assert(is_same<value_to_int_t<128>::type, int16_t>::value, "");
    static_assert(is_same<value_to_int_t<255>::type, int16_t>::value, "");
    static_assert(is_same<value_to_int_t<256>::type, int16_t>::value, "");
    static_assert(is_same<value_to_int_t<70000>::type, int32_t>::value, "");
    static_assert(is_same<value_to_int_t<1'000'000'000>::type, int32_t>::value, "");
    static_assert(is_same<value_to_int_t<40'000'000'000>::type, int64_t>::value, "");
}

TEST_CASE("value_to_uint_t")
{
    static_assert(is_same<value_to_uint_t<10>::type, uint8_t>::value, "");
    static_assert(is_same<value_to_uint_t<127>::type, uint8_t>::value, "");
    static_assert(is_same<value_to_uint_t<128>::type, uint8_t>::value, "");
    static_assert(is_same<value_to_uint_t<255>::type, uint8_t>::value, "");
    static_assert(is_same<value_to_uint_t<256>::type, uint16_t>::value, "");
    static_assert(is_same<value_to_uint_t<70000>::type, uint32_t>::value, "");
    static_assert(is_same<value_to_uint_t<1'000'000'000>::type, uint32_t>::value, "");
    static_assert(is_same<value_to_uint_t<40'000'000'000>::type, uint64_t>::value, "");
}
