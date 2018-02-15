#pragma once

#include "catch.hpp"

namespace mcu {
namespace test {

extern bool expect_failure;

struct expected_failure {
};

struct test_platform {
    static void check(bool ok) {
        if (!ok) {
            if (expect_failure) {
                throw expected_failure();
            }

            FAIL(ok, "Unexpected failure");
        }
    }
};

} // namespace test
} // namespace mcu
