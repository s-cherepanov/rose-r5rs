#include "parsers.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(std::string const& expected) {
    rose::ast_identifier actual;
    ASSERT_TRUE(test_phrase_parser_attr(
                token_p.identifier, expected, skipper_p, actual));
    ASSERT_EQ(actual, rose::ast_identifier(expected));
}

TEST(identifier_parser_test, peculiar_identifier) {
    check("+");
    check("-");
    check("...");
}

TEST(identifier_parser_test, special_initial) {
    check("!");
    check("$");
    check("%");
    check("&");
    check("*");
    check("/");
    check(":");
    check("<");
    check("=");
    check(">");
    check("?");
    check("^");
    check("_");
    check("~");
}

TEST(identifier_parser_test, special_subsequent) {
    check("a+");
    check("a-");
    check("a.");
    check("a@");
}

TEST(identifier_parser_test, mixed ) {
    check("list");
    check("pair?");
    check("set-car!");
    check("string->list");
}
