#include "rose/generator/token.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;
namespace generator = rose::generator;

BOOST_AUTO_TEST_SUITE(boolean_generator_suite)

using ascii::space;

typedef
    generator::character<
        std::back_insert_iterator<std::string>,
        ascii::space_type
    >
    generator_type;

static generator_type g;

BOOST_AUTO_TEST_CASE(boolean_test) {
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, true), "#t ");
    BOOST_CHECK_EQUAL(test_generator_attr_delim(g, space, false), "#f ");
}

BOOST_AUTO_TEST_SUITE_END()
