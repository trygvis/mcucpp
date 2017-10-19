#pragma once

#include <cstdint>
#include "mcu/arm/core_x.h"

namespace mcu {
namespace arm {

#if __CORTEX_M >= 3U

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
    void lock()
    {
        do {
            while (__LDREXB(&locked_) == 1);
        } while (__STREXB(1, &locked_) != 0);
    }

    __always_inline
    void unlock()
    {
        locked_ = 0;
    }
};

#else

//class mutex {
//    static_assert(false, "mcu::arm::mutex is only supported on Cortex cores >= 3.");
//};

#ifndef __always_inline
#define __always_inline
#endif

/**
 * Not really tested
 */
class mutex {
    volatile uint8_t locked_;

public:
    mutex() noexcept : locked_(0)
    {}

    __always_inline
    bool try_lock()
    {
        __disable_irq();

        auto l = locked_;

        if (l == 0) {
            l = locked_ = 1;
        }

        __enable_irq();

        return l;
    }

    __always_inline
    void lock()
    {
        do {
            __disable_irq();
            if (!locked_) {
                locked_ = true;
                return;
            }
            __enable_irq();
        } while (true);
    }

    __always_inline
    void unlock()
    {
        locked_ = 0;
    }
};

#endif // __CORTEX_M >= 3U

} // namespace arm
} // namespace mcu
