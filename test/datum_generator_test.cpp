#include "rose/generator/datum.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;
namespace generator = rose::generator;

using ascii::space;

typedef
    generator::datum<
        std::back_insert_iterator<std::string>,
        ascii::space_type
    >
    generator_type;

static generator_type g;

BOOST_AUTO_TEST_SUITE(datum_generator_suite)

BOOST_AUTO_TEST_CASE(boolean_test) {
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, true), "#t ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, false), "#f ");
}

BOOST_AUTO_TEST_CASE(number_test) {
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, 0), "0 ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, 1), "1 ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, -1), "-1 ");
}

BOOST_AUTO_TEST_CASE(character_test) {
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, ' '), "#\\space ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '\n'), "#\\newline ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '\t'), "#\\tab ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, 'a'), "#\\a ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '\''), "#\\' ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '"'), "#\\\" ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '.'), "#\\. ");
}

BOOST_AUTO_TEST_CASE(list_test) {
    {
        ast_list list;

        list.proper.push_back(1);
        list.proper.push_back(ast_symbol('x'));
        list.proper.push_back(ast_string("hello"));
        list.improper.reset(true);

        BOOST_CHECK_EQUAL(
                test_generator_attr_delim(g, space, ' '),
                "( 1 x \"hello\" . #t ) ");
    }
}

BOOST_AUTO_TEST_SUITE_END()
