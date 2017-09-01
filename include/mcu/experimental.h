#pragma once

#include "mcu/array_view.h"

namespace mcu {

int to_int(const array_view<char> &str);

bool equals(const string_view&, const char *);

struct without_irq {
    __always_inline
    without_irq()
    {
        __disable_irq();
    }

    __always_inline
    ~without_irq()
    {
        __enable_irq();
    }
};

} // namespace mcu
