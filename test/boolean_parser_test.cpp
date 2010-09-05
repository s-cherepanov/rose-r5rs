#include "parsers.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

using namespace rose;

TEST(boolean_parser_test, parse_true) {
    bool attr = false;
    ASSERT_TRUE(test_phrase_parser_attr(
                token_p.boolean, "#t ", skipper_p, attr));
    ASSERT_EQ(attr, true);

}

TEST(boolean_parser_test, parse_false) {
    bool attr = true;
    ASSERT_TRUE(test_phrase_parser_attr(
                token_p.boolean, "#f ", skipper_p, attr));
    ASSERT_EQ(attr, false);
}
