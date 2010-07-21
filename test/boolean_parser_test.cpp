#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( boolean_suite )

BOOST_AUTO_TEST_CASE( boolean_test ) {
    {
        bool attr = false;
        BOOST_CHECK(test_phrase_parser_attr(
                    token_p.boolean, "#t ", skipper_p, attr));
        BOOST_CHECK_EQUAL(attr, true);
    }

    {
        bool attr = true;
        BOOST_CHECK(test_phrase_parser_attr(
                    token_p.boolean, "#f ", skipper_p, attr));
        BOOST_CHECK_EQUAL(attr, false);
    }
}

BOOST_AUTO_TEST_SUITE_END()
