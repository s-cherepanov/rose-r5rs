#include "rose/generator/token.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;
namespace generator = rose::generator;

using ascii::space;

BOOST_AUTO_TEST_SUITE(string_generator_suite)

typedef
    rose::generator::string<
        std::back_insert_iterator<std::string>,
        ascii::space_type
    >
    generator_type;

static generator_type g;

BOOST_AUTO_TEST_CASE(escaping_test) {
    rose::ast_string attr("hello\nworld");
    std::string actual = test_generator_attr_delim(g, space, attr);
    std::string expected("\"hello\nworld\"");
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_SUITE_END()
