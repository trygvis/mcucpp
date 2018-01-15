#pragma once

namespace mcu {

/**
 * \defgroup static_asserts static_assert<> utilities
 *
 * These are the same as calling static_assert<> directly, but makes the error messages a bit prettier as the compilers
 * show the values used when the functions are instantiated.
 *
 *  @{
 */

template<int A, int B>
void static_assert_le() {
    static_assert(A <= B, "A <= B");
}

template<int A, int B>
void static_assert_ge() {
    static_assert(A >= B, "A >= B");
}

template<int A, int B>
void static_assert_eq() {
    static_assert(A == B, "A == B");
}

/** @}*/

} // namespace mcu
