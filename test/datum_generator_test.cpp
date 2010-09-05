#include "generators.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

static void check(rose::ast_datum const& datum, std::string const& expected) {
    ASSERT_EQ(test_generator_attr_delim(datum_g, delimiter_g, datum), expected);
}

TEST(datum_generator_test, generate_boolean) {
    check(true, "#t ");
    check(false, "#f ");
}

TEST(datum_generator_test, generate_number) {
    check(0, "0 ");
    check(1, "1 ");
    check(-1, "-1 ");
}

TEST(datum_generator_test, generate_character) {
    check(' ', "#\\space ");
    check('\n', "#\\newline ");
    check('\t', "#\\tab ");
    check('a', "#\\a ");
    check('\'', "#\\' ");
    check('"', "#\\\" ");
    check('.', "#\\. ");
}

TEST(datum_generator_test, generate_empty_list) {
    rose::ast_list list;
    check(rose::ast_datum(list), "( ) ");
}

TEST(datum_generator_test, generate_flat_list) {
    rose::ast_list list;
    list.elements.push_back(1);
    list.elements.push_back(2);
    list.elements.push_back(3);
    check(rose::ast_datum(list), "( 1 2 3 ) ");
}

TEST(datum_generator_test, generate_mixed_list) {
    rose::ast_list list;
    list.elements.push_back(1);
    list.elements.push_back(rose::ast_symbol("x"));
    list.elements.push_back(rose::ast_string("hello"));
    list.dotted_element.reset(true);
    check(rose::ast_datum(list), "( 1 x \"hello\" . #t ) ");
}
