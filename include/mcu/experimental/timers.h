#pragma once

#include <mcu/util.h>
#include <mcu/nonew/function.h>
#include <cstdio>
#include <type_traits>

#pragma optimize("-O0")

namespace mcu {

template<int Count>
class timers {
    using callback_t = mcu::nonew::function<void()>;
    using bitmap_t = typename mcu::bitmap_t<Count>::type;

public:
    timers() : active_bitmap(0), next_expiry(0) {}

    void once(int i, uint64_t expiry, const callback_t &callback)
    {
        expiry_times[i] = expiry;
        callbacks[i] = callback;
        active_bitmap |= 1 << i;

        if (next_expiry == 0 || expiry < next_expiry) {
            next_expiry = expiry;
        }

        once_bitmap |= 1 << i;
    }

    void repeat(int i, uint64_t first_expiry, uint64_t interval, const callback_t &callback)
    {
        expiry_times[i] = first_expiry;
        interval_times[i] = interval;
        callbacks[i] = callback;
        active_bitmap |= 1 << i;

        if (next_expiry == 0 || first_expiry < next_expiry) {
            next_expiry = first_expiry;
        }
    }

    void loop(uint64_t now)
    {
        if (now >= next_expiry) {
            execute_all_expired(now);
        }
    }

private:
    void execute_all_expired(uint64_t now)
    {
        // Quickly check if there are any active timers
        if (!active_bitmap) {
            return;
        }

//        printf("checking timers: active_bitmap=0x%08" PRIx64 "\n", uint64_t(active_bitmap));

        uint64_t earliest = 0;
        for (int i = 0; i < Count; i++) {
            auto mask = bitmap_t(1 << i);

//            printf("timer %d, active=%d, once=%d, interval=%d, expired=%d\n", i,
//                   active_bitmap & mask,
//                   once_bitmap & mask,
//                   int(once_bitmap & mask ? -1 : interval_times[i]),
//                   now >= expiry_times[i]);

            if (!(active_bitmap & mask)) {
                continue;
            }

            auto expiry = expiry_times[i];

//            breakpoint();
            if (now < expiry) {
                // Not expired yet
                continue;
            }

//            printf("executing timer %d\n", i);
            callbacks[i]();

            if (once_bitmap & mask) {
                callbacks[i] = nullptr;
                once_bitmap &= ~(1 << i);
                active_bitmap &= ~(1 << i);
            } else {
                // Find next expiry time, skip any already missed timeouts
                do {
                    expiry += interval_times[i];
                } while (expiry <= now);

                expiry_times[i] = expiry;
            }

            if (earliest == 0 || expiry < earliest) {
                earliest = expiry;
            }
        }

        next_expiry = earliest;
    }

    bitmap_t active_bitmap;
    bitmap_t once_bitmap;
    uint64_t next_expiry;

    uint64_t expiry_times[Count];
    uint64_t interval_times[Count];
    uint64_t interval[Count];
    callback_t callbacks[Count];
};

};
