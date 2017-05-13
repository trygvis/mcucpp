#pragma once

#include <limits>

template<typename R = std::size_t, typename T, std::size_t N>
static inline constexpr
R SizeOfArray(const T(&array)[N]) {
    static_assert(std::numeric_limits<R>::max() >= N, "N does not fit in R");
    return static_cast<R>(N);
}
