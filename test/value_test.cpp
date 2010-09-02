#include "rose/value.hpp"

#include <boost/test/unit_test.hpp>

using namespace rose;

BOOST_AUTO_TEST_SUITE(value_suite)

BOOST_AUTO_TEST_CASE(handle_cast_test) {
    {
        gc::handle<value> val(make_value(1));
        BOOST_CHECK_EQUAL(handle_cast<int>(val), 1);
    }
}

BOOST_AUTO_TEST_CASE(make_list_nil_test) {
    std::vector<gc::handle<value> > args;
    gc::handle<value> actual = make_list(args);
    BOOST_CHECK(is_nil(actual));
}

BOOST_AUTO_TEST_CASE(make_list_test) {
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

    BOOST_CHECK_EQUAL(out1.str(), out2.str());
}

BOOST_AUTO_TEST_SUITE_END()
