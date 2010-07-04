#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

using namespace rose;

BOOST_AUTO_TEST_SUITE(program_parser_suite)

ast_program parse_program(std::string const& input) {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        parser::intertoken_space<iterator_type>
        skipper_type;

    typedef
        parser::r5rs_grammar<iterator_type, skipper_type>
        r5rs_grammar;

    r5rs_grammar grammar;
    skipper_type skipper;
    ast_program program;

    iterator_type first = input.begin();
    iterator_type last  = input.end();

    bool match = qi::phrase_parse(
            first, last, grammar, skipper, program);

    BOOST_CHECK(match && first == last);

    return program;
}

BOOST_AUTO_TEST_CASE(varaible_test) {
    ast_program expected;

    expected.push_back(ast_expression(ast_variable("x")));
    BOOST_CHECK(parse_program("x") == expected);
}

BOOST_AUTO_TEST_CASE(definition_test) {
    ast_expression e(static_cast<int>(1));
    ast_variable v("x");
    ast_definition d(v, e);
    ast_program expected;

    expected.push_back(d);
    BOOST_CHECK(parse_program("(define x 1)") == expected);
}

BOOST_AUTO_TEST_SUITE_END()
