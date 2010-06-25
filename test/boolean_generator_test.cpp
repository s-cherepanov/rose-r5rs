#include "rose/generator/token.hpp"

#include <boost/spirit/include/karma_generate.hpp>
#include <boost/test/unit_test.hpp>

namespace karma = boost::spirit::karma;
using rose::ast::string;

BOOST_AUTO_TEST_SUITE(boolean_generator_suite)

std::string generate(bool const& b) {
    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    rose::generator::boolean<iterator_type> g;
    karma::generate(sink, g, b);

    return output;
}

BOOST_AUTO_TEST_CASE(boolean_test) {
    BOOST_CHECK_EQUAL(generate(true), "#t");
    BOOST_CHECK_EQUAL(generate(false), "#f");
}

BOOST_AUTO_TEST_SUITE_END()
