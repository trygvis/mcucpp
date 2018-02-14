#pragma once

#include "mcu/internal.h"

namespace mcu {
namespace nonew {

template<typename T, typename SizeType = std::size_t>
class array_ref {
public:
    T *const ptr;
    const SizeType size;

    __always_inline
    T operator[](size_t idx)
    {
        return ptr[start + idx];
    }
};

} // namespace nonew
} // namespace mcu
