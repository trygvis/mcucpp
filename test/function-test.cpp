#include <iostream>
#include "mcu/nonew/function.h"

#include "catch.hpp"

using namespace mcu::nonew;
using std::cout;
using std::endl;

template<typename Sig>
using fn = function<Sig>;

struct my_item {
    int value;

    my_item(int value) : value(value) {
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
    int count = 0;

    fn<void()> f([&]() {
        cout << "wat wat" << endl;
        count = 1;
    });

    REQUIRE(static_cast<bool>(f));
    REQUIRE_FALSE(!f);

    f();
    REQUIRE(count == 1);

    f = [&]() {
        count = 2;
    };
    f();
    REQUIRE(count == 2);

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
