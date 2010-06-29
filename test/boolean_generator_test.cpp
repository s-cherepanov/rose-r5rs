#include "rose/generator/token.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;

namespace generator = rose::generator;

BOOST_AUTO_TEST_SUITE(boolean_generator_suite)

std::string generate(bool const& b) {
    using ascii::space;
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    generator::boolean<iterator_type, space_type> g;
    karma::generate_delimited(sink, g, space, b);

    return output;
}

BOOST_AUTO_TEST_CASE(boolean_test) {
    BOOST_CHECK_EQUAL(generate(true), "#t ");
    BOOST_CHECK_EQUAL(generate(false), "#f ");
}

BOOST_AUTO_TEST_SUITE_END()
