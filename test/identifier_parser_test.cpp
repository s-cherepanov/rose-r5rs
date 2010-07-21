#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(identifier_suite)

void check(std::string const& input, std::string const& expected) {
    rose::ast_identifier actual;
    BOOST_CHECK(test_phrase_parser_attr(
                token_p.identifier, input, skipper_p, actual));
    BOOST_CHECK_EQUAL(actual, rose::ast_identifier(expected));
}

BOOST_AUTO_TEST_CASE(peculiar_identifier_test) {
    check("+", "+");
    check("-", "-");
    check("...", "...");
}

BOOST_AUTO_TEST_CASE(test_special_initial) {
    check("!", "!");
    check("$", "$");
    check("%", "%");
    check("&", "&");
    check("*", "*");
    check("/", "/");
    check(":", ":");
    check("<", "<");
    check("=", "=");
    check(">", ">");
    check("?", "?");
    check("^", "^");
    check("_", "_");
    check("~", "~");
}

BOOST_AUTO_TEST_CASE(test_special_subsequent) {
    check("a+", "a+");
    check("a-", "a-");
    check("a.", "a.");
    check("a@", "a@");
}

BOOST_AUTO_TEST_CASE(test_mixed ) {
    check("list", "list");
    check("pair?", "pair?");
    check("set-car!", "set-car!");
    check("string->list", "string->list");
}

BOOST_AUTO_TEST_SUITE_END()
