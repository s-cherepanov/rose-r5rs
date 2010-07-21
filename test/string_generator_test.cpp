#include "generators.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(string_generator_suite)

namespace ascii = boost::spirit::ascii;

void check(rose::ast_string const& attr, std::string const& expected) {
    BOOST_CHECK_EQUAL(
            test_generator_attr_delim(string_g, delimiter_g, attr),
            expected);
}

BOOST_AUTO_TEST_CASE(escaping_test) {
    check(rose::ast_string("a\nb"), "\"a\nb\" ");
    check(rose::ast_string("a\tb"), "\"a\tb\" ");
    check(rose::ast_string("a\"b"), "\"a\"b\" ");
}

BOOST_AUTO_TEST_SUITE_END()
