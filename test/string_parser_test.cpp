#include "parsers.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(std::string const& input, std::string const& expected) {
    std::string actual;
    ASSERT_TRUE(test_phrase_parser_attr(
                token_p.string, input, skipper_p, actual));
    ASSERT_EQ(actual, expected);
}

TEST(string_parser_test, simple) {
    check("\"abc\"", "abc");
    check("\"\\\"\"", "\"");
    check("\"\\\\\"", "\\");
    check("\" \"", " ");
    check("\"\n\"", "\n");
}
