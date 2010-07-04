#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"

#include <boost/test/unit_test.hpp>

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;
namespace qi = boost::spirit::qi;

using namespace rose;

BOOST_AUTO_TEST_SUITE(program_generator_suite)

std::string generate(ast_program const& program) {
    using ascii::space;
    using ascii::space_type;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    generator::program<iterator_type, space_type> grammar;
    karma::generate_delimited(sink, grammar, space, program);

    return output;
}

ast_program parse(std::string const& input) {
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

BOOST_AUTO_TEST_CASE(variable_test) {
    BOOST_CHECK_EQUAL(generate(parse("x")), "x ");
}

BOOST_AUTO_TEST_CASE(definition_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(define x 1)")),
            "( define x 1 ) ");
}

BOOST_AUTO_TEST_CASE(lambda_expression_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(lambda (x) (* x 2))")),
            "( lambda ( x ) ( * x 2 ) ) ");

    BOOST_CHECK_EQUAL(
            generate(parse(
                    "(lambda (x)\n"
                    "  (define y 2)\n"
                    "  (* x y))")),
            "( lambda ( x ) ( define y 2 ) ( * x y ) ) ");
}

BOOST_AUTO_TEST_CASE(definition_lambda_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(define y (lambda (x) (* x 2)))")),
            "( define y ( lambda ( x ) ( * x 2 ) ) ) ");
}

BOOST_AUTO_TEST_CASE(conditional_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(if x 1 2)")),
            "( if x 1 2 ) ");

    BOOST_CHECK_EQUAL(
            generate(parse("(if x 1)")),
            "( if x 1 ) ");

    BOOST_CHECK_EQUAL(
            generate(parse("(if #t 1)")),
            "( if #t 1 ) ");
}

BOOST_AUTO_TEST_CASE(assignment_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(set! x 1)")),
            "( set! x 1 ) ");
}

BOOST_AUTO_TEST_CASE(quotation_number_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(quote 1)")),
            "( quote 1 ) ");
}

BOOST_AUTO_TEST_CASE(quotation_boolean_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(quote #t)")),
            "( quote #t ) ");

    BOOST_CHECK_EQUAL(
            generate(parse("(quote #f)")),
            "( quote #f ) ");
}

BOOST_AUTO_TEST_CASE(quotation_symbol_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("(quote x)")),
            "( quote x ) ");
}

BOOST_AUTO_TEST_CASE(quotation_abbrev_number_test) {
    BOOST_CHECK_EQUAL(
            generate(parse("'1")),
            "( quote 1 ) ");
}

BOOST_AUTO_TEST_SUITE_END()
