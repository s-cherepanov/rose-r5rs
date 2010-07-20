#include "rose/generator/token.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(character_generator_suite)

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;
namespace generator = rose::generator;

using ascii::space;

typedef
    generator::character<
        std::back_insert_iterator<std::string>,
        ascii::space_type
    >
    generator_type;

static generator_type g;

BOOST_AUTO_TEST_CASE(character_name_test) {
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, ' '), "#\\space ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '\n'), "#\\newline ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '\t'), "#\\tab ");
}

BOOST_AUTO_TEST_CASE(graph_test) {
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, 'a'), "#\\a ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '"'), "#\\\" ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '\''), "#\\' ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, '.'), "#\\. ");
}

BOOST_AUTO_TEST_SUITE_END()
