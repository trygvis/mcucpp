#include "mcu/experimental.h"

namespace mcu {

int to_int(const array_view<char> &str)
{
    int value = 0;

    auto buf = str.underlying();
    auto size = str.size();

    for (int i = 0; i < size; i++) {
        auto c = buf[i];

        if ('0' <= c && c <= '9') {
            value = value * 10 + (c - '0');
        } else {
            return 0;
        }
    }

    return value;
}

bool equals(const string_view &a_view, const char *b_ptr)
{
    const char *a_ptr = a_view.underlying();

    auto size = a_view.size();
    int i = 0;
    for (; i < size; i++) {
        auto b = b_ptr[i];

        if (b == '\0') {
            return false;
        }

        if (a_ptr[i] != b) {
            return false;
        }
    }

    return b_ptr[i] == '\0';
}

} // namespace mcu
