#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( number_suite )

void check(std::string const& input, int expected) {
    int actual;
    BOOST_CHECK(test_phrase_parser_attr(
                token_p.number, input, skipper_p, actual));
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_CASE( number_test ) {
    check( "0", 0 );
    check( "10", 10 );
    check( "-10", -10 );
}

BOOST_AUTO_TEST_SUITE_END()
