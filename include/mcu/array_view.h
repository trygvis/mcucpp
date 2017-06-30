#pragma once

#include <utility>

namespace mcu {

/**
 * An immutable (but assignable) view of an array.
 */
template<typename T>
class array_view {
    T const *buf_;
    int start_;
    int size_;

public:
    array_view(array_view &&other) : buf_(other.buf_), start_(other.start_), size_(other.size_) {}

    array_view() : buf_(nullptr), start_(0), size_(0) {}

    array_view(const T *buf, int size) : buf_(buf), start_(0), size_(size) {}

    array_view(const T *buf, int start, int size) : buf_(buf), start_(start), size_(size) {}

    array_view slice(int start)
    {
        if (start >= size_) {
            return std::move(array_view{0, 0, 0});
        }

        return array_view{&buf_[start_ + start], size_ - start};
    }

    array_view slice(int start, int end)
    {
        if (start >= end) {
            return {};
        }

        return {&buf_[start_ + start], end - start};
    }

    int index_of(T value) const
    {
        return index_of(value, 0);
    }

    int index_of(T value, int start) const
    {
        if (start > size_) {
            return -1;
        }

        auto end = start_ + size_;

        auto *ptr = &buf_[start_];

        int i = start_ + start;

        while (i < end) {
            if (ptr[i] == value) {
                return i - start_;
            }
            i++;
        }

        return -1;
    }

    inline int size() const
    {
        return size_;
    }

    inline T const *underlying() const
    {
        return buf_;
    }

    array_view &operator=(const array_view &other)
    {
        buf_ = other.buf_;
        start_ = other.start_;
        size_ = other.size_;
        return *this;
    }
};

using string_view = array_view<char>;

} // namespace mcu
