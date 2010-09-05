#include "generators.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(rose::ast_string const& attr, std::string const& expected) {
    ASSERT_EQ(test_generator_attr_delim(string_g, delimiter_g, attr), expected);
}

TEST(string_generate_test, generate_escaped_string) {
    check(rose::ast_string("a\nb"), "\"a\nb\" ");
    check(rose::ast_string("a\tb"), "\"a\tb\" ");
    check(rose::ast_string("a\"b"), "\"a\\\"b\" ");
    check(rose::ast_string("a\\b"), "\"a\\\\b\" ");
}
