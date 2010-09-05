#include "parsers.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(std::string const& input, int expected) {
    int actual;
    ASSERT_TRUE(test_phrase_parser_attr(
                token_p.number, input, skipper_p, actual));
    ASSERT_EQ(actual, expected);
}

TEST(number_test, simple) {
    check("0",   0);
    check("10",  10);
    check("-10", -10);
}
