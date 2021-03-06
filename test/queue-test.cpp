#include <mcu/internal.h>
#include <iostream>
#include <functional>
#include "mcu/nonew/function.h"
#include "mcu/nonew/queue.h"
#include "mcu/util.h"

#include "catch.hpp"
#include "test-utils.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

namespace mcu {
namespace test {

using namespace mcu::nonew;
using namespace std;

template<size_t Size>
using queue_t = queue<string, Size, typename mcu::value_to_int_t<Size>::type, test_platform>;

void repeat(int count, std::function<void(int)> f) {
    for (int i = 0; i < count; i++) {
        f(i);
    }
}

template<typename List, typename ...E>
void require_one(__unused const List &list, __unused int i) {
}

template<typename List, typename E, typename ...Es>
void require_one(const List &list, int i, E e, Es...es) {
    REQUIRE(list[i] == e);
    require_one(list, i + 1, es...);
}

template<typename List, typename ...E>
void require_all(List &list, E...es) {
    REQUIRE(list.size() == sizeof...(es));

    require_one(list, 0, es...);
}

TEST_CASE("queue") {
    queue_t<10> event_queue;

    REQUIRE(event_queue.is_empty());

    event_queue.push_back("1");

    REQUIRE(event_queue.size() == 1);
    REQUIRE(event_queue.back() == "1");
    event_queue.pop_back();
    REQUIRE(event_queue.size() == 0);

    expect_failure = true;
    try {
        event_queue.pop_back();
        FAIL("Expected exception");
    } catch (expected_failure &) {
    }

    for (int i = 0; i < event_queue.capacity(); i++) {
        event_queue.push_back(to_string(i));
    }

    expect_failure = true;
    try {
        event_queue.push_back("fail please");
        FAIL("Expected exception");
    } catch (expected_failure &) {
    }
}

template<typename queue>
void print(queue &q) {
    cout << "queue = [";
    for (int i = 0; i < q.size(); i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << q[i];
    }
    cout << "]" << endl << flush;
}

TEST_CASE("push and pop") {
    queue_t<3> q;

    REQUIRE(q.is_empty());

    q.push_back("1");
    q.pop_back();
    print(q);
    require_all(q);

    q.push_back("2");
    q.push_back("3");
    REQUIRE(q.front() == "2");
    REQUIRE(q.back() == "3");
    q.pop_back();
    require_all(q, "2");

    q.push_back("4");
    q.push_back("5");
    print(q);

    require_all(q, "2", "4", "5");
    q.pop_front();
    require_all(q, "4", "5");

    q.push_back("6");
    require_all(q, "4", "5", "6");

    q.pop_front();
    q.push_back("7");
    require_all(q, "5", "6", "7");
    print(q);
}

TEST_CASE("push and pop 2") {
    queue_t<3> q;

    q.push_back("1");
    REQUIRE(q.front() == "1");
    q.pop_front();

    q.push_back("2");
    REQUIRE(q.front() == "2");
    q.pop_front();

    q.push_back("3");
    REQUIRE(q.front() == "3");
    q.pop_front();

    q.push_back("4");
    REQUIRE(q.front() == "4");
    q.pop_front();
}

} // namespace test
} // namespace mcu
