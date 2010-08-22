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

BOOST_AUTO_TEST_SUITE_END()
