#pragma once

#include <memory>
#include <cstring>
#include <mcu/experimental/static_assert.h>

#ifndef MCU_LOG
#define MCU_LOG() do {} while(false)
#endif

namespace mcu {
namespace nonew {

template<typename Signature, std::size_t Size = sizeof(void *) * 3>
class function;

template<typename Ret, typename ...Args, std::size_t Size>
class function<Ret(Args...), Size> {
    class Invoker;

public:
    using Signature = Ret(Args...);
    typedef Ret return_type;
    static const std::size_t alloc_size = Size + sizeof(Invoker);

    explicit function() : valid_(false), storage_() {
        MCU_LOG();
    }

    ~function() {
        MCU_LOG();
        destruct();
    }

    template<typename Func>
    function(Func &&func) : storage_() {
        MCU_LOG();
        assign(std::forward<Func>(func));
    }

    function(const function &other) noexcept : valid_(other.valid_), storage_() {
        MCU_LOG();
        if (valid_) {
            std::memcpy(storage_, other.storage_, alloc_size);
        }
    }

    function(function &other) noexcept : valid_(other.valid_), storage_() {
        MCU_LOG();
        if (valid_) {
            std::memcpy(storage_, other.storage_, alloc_size);
        }
    }

    function(const function &&other) noexcept : valid_(other.valid_), storage_() {
        MCU_LOG();
        if (valid_) {
            std::memcpy(storage_, other.storage_, alloc_size);
        }
    }

    function(function &&other) noexcept : valid_(other.valid_), storage_() {
        MCU_LOG();
        if (valid_) {
            std::memcpy(storage_, other.storage_, alloc_size);
        }
    }

    function &operator=(std::nullptr_t) {
        MCU_LOG();
        destruct();
        return *this;
    }

    function &operator=(const function &other) {
        MCU_LOG();

        if (&other == this) {
            return *this;
        }

        destruct();
        valid_ = other.valid_;
        if (valid_) {
            std::memcpy(storage_, other.storage_, alloc_size);
        }

        return *this;
    }

    function &operator=(function &other) {
        return operator=(static_cast<const function>(other));
    }

    function &operator=(function &&other) {
        MCU_LOG();
        destruct();
        valid_ = other.valid_;
        if (valid_) {
            std::memcpy(storage_, other.storage_, alloc_size);
        }
        other.destruct();
        return *this;
    }

    template<typename Func>
    function &operator=(const Func &func) {
        MCU_LOG();
        destruct();
        assign(std::forward<Func>(func));
        return *this;
    }

    template<typename Func>
    function &operator=(Func &&func) {
        MCU_LOG();
        destruct();
        assign(std::forward<Func>(func));
        return *this;
    }

    operator bool() const {
        return valid_;
    }

    bool operator!() const {
        return !valid_;
    }

    Ret operator()(Args... args) {
        return invoker()->invoke(args...);
    }

    Ret operator()(Args... args) const {
        return invoker()->invoke(args...);
    }

private:
    bool valid_;
    uint8_t storage_[alloc_size];

    __attribute__((always_inline))
    const Invoker *invoker() const {
        return reinterpret_cast<const Invoker *>(storage_);
    }

    template<typename Func>
    void assign(Func &&func) {

        typedef typename std::decay<Func>::type RealFunc;
        typedef FuncHolder <RealFunc> holder_t;

        static_assert_ge<alloc_size, sizeof(holder_t)>();
        static_assert_ge<alloc_size, sizeof(RealFunc)>();

        auto tmp = new(&storage_)holder_t(std::forward<RealFunc>(func));
        static_cast<void>(tmp);

        valid_ = true;
    }

    void destruct() {
        if (valid_) {
            auto *i = invoker();
            i->~Invoker();
        }
        valid_ = false;
    }

    struct Invoker {
        virtual ~Invoker() = default;

        virtual Ret invoke(Args... args) = 0;

        virtual Ret invoke(Args... args) const = 0;
    };

    template<typename Value>
    struct FuncHolder : public Invoker {
        virtual ~FuncHolder() = default;

        explicit FuncHolder(Value &&value) : value(std::forward<Value>(value)) {}

        virtual Ret invoke(Args... args) {
            return value(std::forward<Args>(args)...);
        }

        virtual Ret invoke(Args... args) const {
            return value(std::forward<Args>(args)...);
        }

        Value value;
    };
};

} // namespace nonew
} // namespace mcu

#undef MCU_LOG
