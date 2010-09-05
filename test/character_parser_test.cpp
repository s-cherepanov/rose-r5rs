#include "parsers.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(std::string const& input, char expected) {
    char actual = 0;
    ASSERT_TRUE(test_phrase_parser_attr(
                token_p.character, input, skipper_p, actual));
    ASSERT_EQ(actual, expected);
}

TEST(character_parser_test, parse_normal_character) {
    check( "#\\a", 'a' );
    check( "#\\?", '?' );
    check( "#\\\\", '\\' );
    check( "#\\'", '\'' );
    check( "#\\\"", '"' );
}

TEST(character_parser_test, parse_character_name) {
    check( "#\\space", ' ' );
    check( "#\\newline", '\n' );
    check( "#\\tab", '\t' );
}
