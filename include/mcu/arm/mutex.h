#pragma once

namespace mcu {
namespace arm {

class mutex {
    volatile uint8_t locked;

public:
    mutex() noexcept : locked(0)
    {}

    __always_inline
    bool try_lock()
    {
        auto l = __LDREXB(&locked);

        if (l == 1) {
            return false;
        }

        return __STREXB(1, &locked) == 0;
    }

    __always_inline
    bool lock()
    {
        do {
            while (__LDREXB(&locked) == 1);
        } while (__STREXB(1, &locked) != 0);
    }

    __always_inline
    bool unlock()
    {
        locked = 0;
    }
};

} // namespace arm
} // namespace mcu
