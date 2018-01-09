#pragma once

#include <array>
#include <numeric>
#include <limits>

#include <mcu/util.h>

extern "C"
__attribute__((noreturn))
int halt();

namespace mcu {
namespace nonew {

struct mcu_default_platform {
    static
    void check(bool ok) {
        if (!ok) {
            ::halt();
        }
    }
};

template<typename T, size_t Capacity_, typename idx_t = typename mcu::value_to_int_t<Capacity_>::type, typename platform = mcu_default_platform>
class queue {
public:
    using element_type = T;
    using IdxT = idx_t;
    static const size_t Capacity = Capacity_;

private:
    static_assert(std::numeric_limits<idx_t>::max() >= Capacity, "The index type is too small for the given capacity");
    static_assert(std::numeric_limits<idx_t>::is_signed, "The index type must be signed");

    static const idx_t capacity_ = static_cast<idx_t>(Capacity);

private:
    using ValueType = T;

    T array[Capacity];
    idx_t head, size_;

    __always_inline
    idx_t wrap(int idx) const {
        int value = idx >= capacity_ ? idx_t(idx - capacity_) : idx;
        return static_cast<idx_t>(value);
    }

    idx_t logical_to_physical(idx_t i) const {
        platform::check(i < Capacity);

        idx_t idx = head + i;

        return wrap(idx);
    }

    idx_t after_tail_idx() const {
        platform::check(size_ < Capacity);

        idx_t tail = head + size_;

        return wrap(tail);
    }

public:
    queue() : head(0), size_(0) {
    }

    queue(const queue &) = delete;

    queue(queue &&) = delete;

    bool is_empty() const {
        return size_ == 0;
    }

    bool is_full() const {
        return size_ >= Capacity;
    }

    idx_t capacity() {
        return capacity_;
    }

    idx_t size() const {
        return size_;
    }

    void clear() {
        head = size_ = 0;
    }

    template<typename U>
    void push_back(U &&item) {
        auto tail = after_tail_idx();
        void *location = &array[tail];

        new(location) ValueType(std::forward<U>(item));

        size_++;
    }

    T &operator[](idx_t index) {
        idx_t idx = logical_to_physical(index);

        auto *ptr = &array[idx];
        return *reinterpret_cast<T *>(ptr);
    }

    const T &operator[](idx_t index) const {
        idx_t idx = logical_to_physical(index);

        auto *ptr = &array[idx];
        return *reinterpret_cast<const T *>(ptr);
    }

    T &back() {
        platform::check(!is_empty());

        return this->operator[](size_ - 1);
    }

    T &front() {
        platform::check(!is_empty());

        return this->operator[](0);
    }

    void pop_front() {
        platform::check(!is_empty());

        head = wrap(head + 1);
        size_--;
        platform::check(size_ >= 0);
    }

    void pop_back() {
        platform::check(!is_empty());

        size_--;
        platform::check(size_ >= 0);
    }
};

} // namespace nonew
} // namespace mcu
