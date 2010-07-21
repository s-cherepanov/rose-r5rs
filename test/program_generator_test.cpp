#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(program_generator_suite)

using boost::spirit::ascii::space;
using boost::spirit::ascii::space_type;

struct fixture {
    typedef
        rose::parser::intertoken_space<std::string::const_iterator>
        skipper_type;

    typedef
        rose::parser::r5rs_grammar<
            std::string::const_iterator,
            skipper_type
        >
        parser_type;

    typedef
        rose::generator::program<
            std::back_insert_iterator<std::string>,
            space_type
        >
        generator_type;

    parser_type parser;
    generator_type generator;
    skipper_type skipper;

    void check(std::string const& input, std::string const& expected) {
        rose::ast_program attr;
        test_phrase_parser_attr(parser, input, skipper, attr);

        BOOST_CHECK_EQUAL(
                test_generator_attr_delim(generator, space, attr),
                expected);
    }

};  //  struct fixture

BOOST_FIXTURE_TEST_CASE(variable_test, fixture) {
    check("x", "x ");
}

BOOST_FIXTURE_TEST_CASE(definition_test, fixture) {
    check("(define x 1)", "( define x 1 ) ");
}

BOOST_FIXTURE_TEST_CASE(lambda_expression_test, fixture) {
    check(
            "(lambda (x) (* x 2))",
            "( lambda ( x ) ( * x 2 ) ) "
    );

    check(
            "(lambda (x)\n"
            "  (define y 2)\n"
            "  (* x y))",

            "( lambda ( x ) ( define y 2 ) ( * x y ) ) "
    );
}

BOOST_FIXTURE_TEST_CASE(definition_lambda_test, fixture) {
    check(
            "(define y (lambda (x) (* x 2)))",
            "( define y ( lambda ( x ) ( * x 2 ) ) ) "
    );
}

BOOST_FIXTURE_TEST_CASE(conditional_test, fixture) {
    check("(if x 1 2)", "( if x 1 2 ) ");
    check("(if x 1)",   "( if x 1 ) ");
    check("(if #t 1)",  "( if #t 1 ) ");
}

BOOST_FIXTURE_TEST_CASE(assignment_test, fixture) {
    check("(set! x 1)", "( set! x 1 ) ");
}

BOOST_FIXTURE_TEST_CASE(quotation_number_test, fixture) {
    check("(quote 1)", "( quote 1 ) ");
}

BOOST_FIXTURE_TEST_CASE(quotation_boolean_test, fixture) {
    check("(quote #t)", "( quote #t ) ");
    check("(quote #f)", "( quote #f ) ");
}

BOOST_FIXTURE_TEST_CASE(quotation_symbol_test, fixture) {
    check("(quote x)", "( quote x ) ");
}

BOOST_FIXTURE_TEST_CASE(quotation_abbrev_number_test, fixture) {
    check("'1", "( quote 1 ) ");
}

BOOST_AUTO_TEST_SUITE_END()
