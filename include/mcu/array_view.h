#pragma once

#include <mcu/internal.h>

#include <utility>
#include <cstring>

namespace mcu {

/**
 * An immutable (but assignable) view of an array of type T. Instances wrapping arrays (not pointers) can be constructed with constexpr. This gives a
 * nice API for string literals.
 *
 * ### Example
 *
 * \snippet array_view-test.cpp String literal converted to array_view
 */
template<typename T>
class array_view {
    T const *buf_;
    int start_;
    int size_;

public:
    array_view(array_view &&other) noexcept : buf_(other.buf_), start_(other.start_), size_(other.size_) {}

    array_view(const array_view &other) noexcept : buf_(other.buf_), start_(other.start_), size_(other.size_) {}

    array_view() noexcept : buf_(nullptr), start_(0), size_(0) {}

    array_view(const T *buf, int size) noexcept : buf_(buf), start_(0), size_(size) {}

    array_view(const T *buf, int start, int size) noexcept : buf_(buf), start_(start), size_(size) {}

    array_view slice(int start) const
    {
        if (start >= size_) {
            return std::move(array_view{0, 0, 0});
        }

        return array_view{&buf_[start_ + start], size_ - start};
    }

    array_view slice(int start, int end) const
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

    inline T const *data() const
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

// This is probably a bad idea, "strings" imply zero-termination.
using string_view = array_view<char>;

__unused
static
string_view make_string_view(const char *str) noexcept
{
    auto len = static_cast<int>(std::strlen(str));
    return {str, len};
}

template<std::size_t N>
__unused static constexpr
string_view make_string_view(const char (&str)[N]) noexcept
{
    return {str, static_cast<int>(N - 1)};
}

} // namespace mcu
