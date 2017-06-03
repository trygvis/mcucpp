#pragma once

namespace mcu {
namespace arm {

class mutex {
    volatile uint8_t locked_;

public:
    mutex() noexcept : locked_(0)
    {}

    __always_inline
    bool try_lock()
    {
        auto l = __LDREXB(&locked_);

        if (l == 1) {
            return false;
        }

        return __STREXB(1, &locked_) == 0;
    }

    __always_inline
    bool lock()
    {
        do {
            while (__LDREXB(&locked_) == 1);
        } while (__STREXB(1, &locked_) != 0);
    }

    __always_inline
    bool unlock()
    {
        locked_ = 0;
    }
};

} // namespace arm
} // namespace mcu
