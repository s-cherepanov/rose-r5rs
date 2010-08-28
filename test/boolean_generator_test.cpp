#include "generators.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(boolean_generator_suite)

BOOST_AUTO_TEST_CASE(boolean_test) {
    BOOST_CHECK_EQUAL(
            test_generator_attr_delim(boolean_g, delimiter_g, true),
            "#t ");

    BOOST_CHECK_EQUAL(
            test_generator_attr_delim(boolean_g, delimiter_g, false),
            "#f ");
}

BOOST_AUTO_TEST_SUITE_END()
