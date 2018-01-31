#pragma once

#include <cstdint>
#include "mcu/arm/core_x.h"

#ifndef __always_inline
#define __always_inline
#endif

namespace mcu {
namespace arm {

/**
 * A BasicLockable.
 *
 * See http://en.cppreference.com/w/cpp/concept/BasicLockable
 *
 * __STREXB(value, address) returns 0 if the address has not been referenced since the previous __LDREXB().
 */
class mutex;

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

    __always_inline
    bool is_locked()
    {
        return locked_ == 1;
    }
};

#endif

#if defined(__CORTEX_M) && __CORTEX_M < 3U

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

        bool got_lock = locked_ == 0;

        if (got_lock) {
            locked_ = 1;
        }

        __enable_irq();

        return got_lock;
    }

    __always_inline
    void lock()
    {
        do {
            __disable_irq();
            if (!locked_) {
                locked_ = 1;
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

    __always_inline
    bool is_locked()
    {
        __disable_irq();
        auto l = locked_ == 1;
        __enable_irq();
        return l;
    }
};

#endif // __CORTEX_M >= 3U

} // namespace arm
} // namespace mcu
