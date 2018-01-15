#include <iostream>
#include <mcu/internal.h>
#include "catch.hpp"

#ifndef MCU_FUNCTION_DEBUG
#define MCU_FUNCTION_DEBUG 1
#endif

#if MCU_FUNCTION_DEBUG
#define MCU_LOG() do {std::cout << __PRETTY_FUNCTION__ << std::endl;} while(false)
#endif

#include "mcu/nonew/function.h"

using namespace mcu::nonew;
using std::cout;
using std::endl;

template<typename Sig>
using fn = function<Sig>;

struct my_item {
    int value;

    explicit my_item(int value) : value(value) {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    my_item(const my_item &other) : value(other.value) {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    ~my_item() {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

class my_class {
    function<void(int *a)> callback;

    void work(int value) {
        int *int_ptr = &value;
        callback.operator()(int_ptr);
    }
};

TEST_CASE("function") {
    int marker = 0;

    fn<void()> f([&]() {
        marker = 1;
    });

    REQUIRE(static_cast<bool>(f));
    REQUIRE_FALSE(!f);

    f();
    REQUIRE(marker == 1);

    f = [&]() {
        marker = 2;
    };
    f();
    REQUIRE(marker == 2);

    fn<void()> b;

    b = std::move(f);
    REQUIRE(b);
    REQUIRE_FALSE(f);

    b = nullptr;
    REQUIRE_FALSE(b);

//    {
//        my_item item(10);
//        cout << "item created" << endl;
//        auto x = ([item]() {
//            cout << "with item: " << item.value << endl;
//        });
//        fn<void()> b;
//        b = x;
//        cout << "b created" << endl;
//        b();
//        cout << "b invoked" << endl;
//    }
    cout << "done" << endl;
}

TEST_CASE("function can be copied") {
    auto l = [](){};
    fn<void()> a, b(l);

    // A function can be copied. Both remain valid.
    REQUIRE_FALSE(a);
    REQUIRE(b);
    a = b;
    REQUIRE(a);
    REQUIRE(b);
}

TEST_CASE("function can be moved") {
    auto l = [](){};
    fn<void()> a, b(l);

    // A function can be moved. The moved-from is invalidated.
    REQUIRE_FALSE(a);
    REQUIRE(b);
    a = std::move(b);
    REQUIRE(a);
    REQUIRE_FALSE(b);
}

#if 0
void do_something_else(int args, fn<void(int)> cb) {
    cout << __PRETTY_FUNCTION__ << endl;

    cb(args);
}

void do_something(__unused fn<void(bool)> cb) {
    cout << __PRETTY_FUNCTION__ << endl;

    do_something_else(123, [cb](int args) {
        cout << "do something callback: args=" << args << endl;
        cb(true);
    });
}

void outer() {
    cout << __PRETTY_FUNCTION__ << endl;

    do_something([](bool ok) {
        cout << "Inside main callback, ok=" << ok << endl;
    });
}

TEST_CASE("function woot") {
    outer();
}
#endif
