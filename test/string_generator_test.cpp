#include "rose/generator/token.hpp"

#include <boost/test/unit_test.hpp>

namespace ast = rose::ast;
namespace karma = boost::spirit::karma;

BOOST_AUTO_TEST_SUITE(string_generator_suite)

std::string generate(rose::ast::string const& s) {
    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    rose::generator::string<iterator_type> g;
    karma::generate(sink, g, s);

    return output;
}

BOOST_AUTO_TEST_CASE(escaping_test) {
    std::string actual = generate(ast::string("hello\nworld"));
    std::string expected = "\"hello\nworld\"";
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_SUITE_END()
