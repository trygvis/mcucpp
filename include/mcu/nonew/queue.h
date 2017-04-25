#pragma once

#include <array>
#include <numeric>
#include <limits>

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

template<typename T, size_t Capacity, typename platform = mcu_default_platform>
class queue {
public:
    typedef ssize_t idx_t;
    typedef T element_type;

    static_assert(std::numeric_limits<idx_t>::max() >= Capacity, "The selected index type is too small");
    static const idx_t capacity = static_cast<idx_t>(Capacity);

private:
    using ValueType = T;

    T array[Capacity];
    idx_t head, size_;

    idx_t head_idx() {
        return head;
    }

    idx_t logical_to_physical(idx_t i) const {
        platform::check(i < Capacity);

        idx_t idx = head + i;

        return idx >= Capacity ? idx_t(idx - Capacity) : idx;
    }

    idx_t tail_idx() const {
        platform::check(size_ < Capacity);

        idx_t tail = head + size_ - 1;

        return tail >= Capacity ? idx_t(tail - Capacity) : tail;
    }

    idx_t after_tail_idx() const {
        platform::check(size_ < Capacity);

        idx_t tail = head + size_;

        return tail >= Capacity ? idx_t(tail - Capacity) : tail;
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
        return size_ == Capacity;
    }

    idx_t size() const {
        return size_;
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

        head++;
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
