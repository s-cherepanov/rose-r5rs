#include "generators.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(datum_generator_suite)

void check(rose::ast_datum const& datum, std::string const& expected) {
    BOOST_CHECK_EQUAL(
            test_generator_attr_delim(datum_g, delimiter_g, datum),
            expected);
}

BOOST_AUTO_TEST_CASE(boolean_test) {
    check(true, "#t ");
    check(false, "#f ");
}

BOOST_AUTO_TEST_CASE(number_test) {
    check(0, "0 ");
    check(1, "1 ");
    check(-1, "-1 ");
}

BOOST_AUTO_TEST_CASE(character_test) {
    check(' ', "#\\space ");
    check('\n', "#\\newline ");
    check('\t', "#\\tab ");
    check('a', "#\\a ");
    check('\'', "#\\' ");
    check('"', "#\\\" ");
    check('.', "#\\. ");
}

BOOST_AUTO_TEST_CASE(empty_list_test) {
    rose::ast_list list;
    check(rose::ast_datum(list), "( ) ");
}

BOOST_AUTO_TEST_CASE(flat_list_test) {
    rose::ast_list list;
    list.elements.push_back(1);
    list.elements.push_back(2);
    list.elements.push_back(3);
    check(rose::ast_datum(list), "( 1 2 3 ) ");
}

BOOST_AUTO_TEST_CASE(mixed_list_test) {
    rose::ast_list list;
    list.elements.push_back(1);
    list.elements.push_back(rose::ast_symbol("x"));
    list.elements.push_back(rose::ast_string("hello"));
    list.dotted_element.reset(true);
    check(rose::ast_datum(list), "( 1 x \"hello\" . #t ) ");
}

BOOST_AUTO_TEST_SUITE_END()
