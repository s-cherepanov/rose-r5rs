#include "rose/value.hpp"

#include <gtest/gtest.h>

using namespace rose;

TEST(value_test, handle_cast) {
    {
        gc::handle<value> val(make_value(1));
        ASSERT_EQ(handle_cast<int>(val), 1);
    }
}

TEST(value_test, make_list_nil) {
    std::vector<gc::handle<value> > args;
    gc::handle<value> actual = make_list(args);
    ASSERT_TRUE(is_nil(actual));
}

TEST(value_test, make_list) {
    std::vector<gc::handle<value> > args;
    args.push_back(make_value(1));
    args.push_back(make_value(rs_symbol("hello")));
    args.push_back(make_value(rs_string("world")));

    rs_pair actual = handle_cast<rs_pair>(make_list(args));

    rs_pair expected(
            make_value(1),
            make_value(rs_pair(
                    make_value(rs_symbol("hello")),
                    make_value(rs_pair(
                            make_value(rs_string("world")))))));

    std::ostringstream out1, out2;
    out1 << actual;
    out2 << expected;

    ASSERT_EQ(out1.str(), out2.str());
}
