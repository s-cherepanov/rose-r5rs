#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(string_suite)

void check(std::string const& input, std::string const& expected) {
    std::string actual;
    BOOST_CHECK(test_phrase_parser_attr(
                token_p.string, input, skipper_p, actual));
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_CASE(string_test) {
    check("\"abc\"", "abc");
    check("\"\\\"\"", "\"");
    check("\"\\\\\"", "\\");
    check("\" \"", " ");
    check("\"\n\"", "\n");
}

BOOST_AUTO_TEST_SUITE_END()
