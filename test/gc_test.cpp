#include "rose/gc/gc.hpp"
#include "rose/gc/handle.hpp"
#include "rose/gc/object.hpp"

#include <gtest/gtest.h>

namespace gc = rose::gc;

using gc::handle;
using gc::object;

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

TEST(gc_test, simple_gc) {
    {
        handle<garbage> h(new object<garbage>);
        ASSERT_TRUE(garbage::existing);
    }

    gc::force_gc();
    ASSERT_FALSE(garbage::existing);
}

struct to {};
struct from : to {};

TEST(gc_test, conversion) {
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

TEST(gc_test, empty_handle) {
    handle<int> h;
    gc::force_gc();
}

TEST(gc_test, force_gc) {
    gc::force_gc();
}
