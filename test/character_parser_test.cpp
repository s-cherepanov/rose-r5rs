#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(character_suite)

void check(std::string const& input, char expected) {
    char actual = 0;
    BOOST_CHECK(test_phrase_parser_attr(
                token_p.character, input, skipper_p, actual));
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_CASE(test_any_character) {
    check( "#\\a", 'a' );
    check( "#\\?", '?' );
}

BOOST_AUTO_TEST_CASE(test_character_name) {
    check( "#\\space", ' ' );
    check( "#\\newline", '\n' );
}

BOOST_AUTO_TEST_SUITE_END()
