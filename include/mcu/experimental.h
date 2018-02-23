#pragma once

#include "mcu/array_view.h"

namespace mcu {

int to_int(const array_view<char> &str);

bool equals(const string_view &, const char *);

template<typename T>
bool starts_with(const array_view<T> &a_view, const array_view<T> &b_view)
{
    if (b_view.size() > a_view.size()) {
        return false;
    }

    auto a = a_view.data();
    auto b = b_view.data();
    for (int i = 0; i < b_view.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool contains(const array_view<T> &haystack, const array_view<T> &needle)
{
    int nz = needle.size();
    if (nz > haystack.size()) {
        return false;
    }

    auto end = haystack.size() - nz;
    for (int i = 0; i < end; i++) {
        auto idx = haystack.index_of(needle.data()[0], i);
        if (idx != -1 && starts_with(haystack.slice(idx), needle)) {
            return true;
        }
    }

    return false;
}

#ifdef CONFIG_ARM

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

#endif

} // namespace mcu
