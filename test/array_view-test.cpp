#include <iostream>
#include <functional>
#include <cstring>
#include "mcu/array_view.h"
#include "mcu/experimental.h"

#include "catch.hpp"
#include "test-utils.h"

using namespace mcu;

namespace mcu {
namespace test {

//! [String literal converted to array_view]
bool is_2(string_view str) {
    return str.size() == 2;
}

void foo() {
    is_2(make_string_view("2"));
}
//! [String literal converted to array_view]

TEST_CASE("array_view")
{
    const char data[] = "1234567890\0";

    string_view v1;

    REQUIRE(v1.size() == 0);
    REQUIRE(v1.data() == nullptr);

    string_view v2{data, 10};
    REQUIRE(v2.size() == 10);
    REQUIRE(v2.data() == data);
}

TEST_CASE("array_view::slice")
{
    const char data[] = "1234567890";

    string_view v1{data, 10};
    REQUIRE(v1.slice(0).data() == data);
    REQUIRE(v1.slice(0).size() == 10);
    REQUIRE(v1.slice(20).size() == 0);

    auto v2 = v1.slice(4);
    REQUIRE(v2.size() == 6);
    REQUIRE(v2.data() == &data[4]);

    REQUIRE(memcmp("567890", v2.data(), 6) == 0);
    REQUIRE(v1.slice(2, 6).size() == 4);
    REQUIRE(memcmp("3456", v1.slice(2, 6).data(), 4) == 0);
}

TEST_CASE("array_view::index_of")
{
    auto v1 = make_string_view("a bb ccc");
    REQUIRE(v1.index_of(' ') == 1);
    REQUIRE(v1.index_of(' ', 1) == 1);
    REQUIRE(v1.index_of(' ', 2) == 4);

    auto v2 = v1.slice(2, 5);
    REQUIRE(v2.index_of(' ') == 2);
    REQUIRE(v2.index_of(' ', 1) == 2);
    REQUIRE(v2.index_of(' ', 2) == 2);
    REQUIRE(v2.index_of(' ', 3) == -1);
    REQUIRE(v2.index_of(' ', 4) == -1);
}

} // namespace test
} // namespace mcu
