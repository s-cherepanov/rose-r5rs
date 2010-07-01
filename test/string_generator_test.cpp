#include "rose/generator/token.hpp"

#include <boost/test/unit_test.hpp>

using namespace rose;

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;

BOOST_AUTO_TEST_SUITE(string_generator_suite)

std::string generate(rose::ast_string const& s) {
    using ascii::space;
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    rose::generator::string<iterator_type, space_type> g;
    karma::generate_delimited(sink, g, space, s);

    return output;
}

BOOST_AUTO_TEST_CASE(escaping_test) {
    std::string actual = generate(ast_string("hello\nworld"));
    std::string expected = "\"hello\nworld\" ";
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_SUITE_END()
