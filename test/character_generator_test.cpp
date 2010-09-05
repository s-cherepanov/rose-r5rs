#include "generators.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(char ch, std::string const& expected) {
    using boost::spirit::karma::delimit;
    using boost::spirit::karma::no_delimit;

    ASSERT_EQ(
            test_generator_attr_delim(
                character_g, delimiter_g, ch),
            expected);
}

TEST(character_generator_test, generate_character_name) {
    check(' ', "#\\space ");
    check('\t', "#\\tab ");
    check('\n', "#\\newline ");
}

TEST(character_generator_test, generate_graph) {
    check('a', "#\\a ");
    check('"', "#\\\" ");
    check('"', "#\\\" ");
    check('\'', "#\\' ");
    check('.', "#\\. ");
}
