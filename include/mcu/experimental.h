#pragma once

#include "mcu/array_view.h"

namespace mcu {

int to_int(const array_view<char> &str);

bool equals(const string_view&, const char *);

} // namespace mcu
