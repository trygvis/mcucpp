#include <iostream>
#include <functional>
#include <cstring>
#include "mcu/array_view.h"
#include "mcu/experimental.h"
#include "mcu/experimental/bits.h"

#include "test-utils.h"

using namespace mcu;

TEST_CASE("to_int")
{
    const char data[] = "1234567890\0";

    string_view v1{data, 10};

    REQUIRE(to_int(v1) == 1234567890);
    REQUIRE(to_int(v1.slice(0)) == 1234567890);
    REQUIRE(to_int(v1.slice(9)) == 0);
    REQUIRE(to_int(v1.slice(8)) == 90);
    REQUIRE(to_int(v1.slice(2, 3)) == 3);
    REQUIRE(to_int(v1.slice(2, 6)) == 3456);
}

TEST_CASE("equals")
{
    const char data[] = "1234567890\0";

    REQUIRE(equals(string_view("123"), "123"));
    REQUIRE(!equals(string_view("123 "), "123"));
    REQUIRE(!equals(string_view("123"), "123 "));

    REQUIRE(!equals(string_view("abc123xyz").slice(3, 6), "123 "));
    REQUIRE(equals(string_view("abc123xyz").slice(3, 6), "123"));
}

TEST_CASE("starts_with")
{
    string_view raw("---1234567890---");

    auto x = raw.slice(3, 13);

    REQUIRE(x.size() == 10);
    REQUIRE(mcu::starts_with<char>(x, "123"));
    REQUIRE_FALSE(mcu::starts_with<char>(x, "321"));
    REQUIRE_FALSE(mcu::starts_with<char>(x, "1234567890abc"));
}

TEST_CASE("bits")
{
    REQUIRE(bits::is_set(0x10, 4));
}
