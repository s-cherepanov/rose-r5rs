#include "rose/gc/gc.hpp"
#include "rose/gc/handle.hpp"
#include "rose/gc/object.hpp"

#include <boost/test/unit_test.hpp>

namespace gc = rose::gc;

using gc::handle;
using gc::object;

BOOST_AUTO_TEST_SUITE(gc_suite)

struct garbage {
    static bool existing;

    garbage() {
        existing = true;
    }

    ~garbage() {
        existing = false;
    }

};  //  struct garbage

bool garbage::existing = true;

BOOST_AUTO_TEST_CASE(simple_gc_test) {
    gc::init();

    {
        handle<garbage> h(new object<garbage>);
        BOOST_CHECK(garbage::existing);
    }

    gc::force_gc();
    BOOST_CHECK(!garbage::existing);
}

struct to {};
struct from : to {};

BOOST_AUTO_TEST_CASE(conversion_test) {
    gc::init();

    {
        handle<from> h1(new object<from>);
        handle<to> h2(h1), h3 = h1, h4;
        h4 = h1;
    }

    {
        handle<from> h1;
        handle<to> h2(h1), h3 = h1, h4;
        h4 = h1;
    }

    gc::force_gc();
}

BOOST_AUTO_TEST_CASE(empty_handle_test) {
    gc::init();
    handle<int> h;
}

BOOST_AUTO_TEST_SUITE_END()
