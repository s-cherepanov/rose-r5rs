#include "generators.hpp"
#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(program_generator_suite)

using namespace rose;

void check(std::string const& input, std::string const& expected) {
    ast_program attr;
    BOOST_CHECK(test_phrase_parser_attr(program_p, input, skipper_p, attr));

    BOOST_CHECK_EQUAL(
            test_generator_attr_delim(program_g, delimiter_g, attr),
            expected);
}

BOOST_AUTO_TEST_CASE(variable_test) {
    check("x", "x ");
}

BOOST_AUTO_TEST_CASE(definition_test) {
    check("(define x 1)", "( define x 1 ) ");
}

BOOST_AUTO_TEST_CASE(lambda_expression_test) {
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

BOOST_AUTO_TEST_CASE(definition_lambda_test) {
    check(
            "(define y (lambda (x) (* x 2)))",
            "( define y ( lambda ( x ) ( * x 2 ) ) ) "
    );
}

BOOST_AUTO_TEST_CASE(conditional_test) {
    check("(if x 1 2)", "( if x 1 2 ) ");
    check("(if x 1)",   "( if x 1 ) ");
    check("(if #t 1)",  "( if #t 1 ) ");
}

BOOST_AUTO_TEST_CASE(assignment_test) {
    check("(set! x 1)", "( set! x 1 ) ");
}

BOOST_AUTO_TEST_CASE(quotation_number_test) {
    check("(quote 1)", "( quote 1 ) ");
}

BOOST_AUTO_TEST_CASE(quotation_boolean_test) {
    check("(quote #t)", "( quote #t ) ");
    check("(quote #f)", "( quote #f ) ");
}

BOOST_AUTO_TEST_CASE(quotation_symbol_test) {
    check("(quote x)", "( quote x ) ");
}

BOOST_AUTO_TEST_CASE(quotation_abbrev_number_test) {
    check("'1", "( quote 1 ) ");
}

BOOST_AUTO_TEST_SUITE_END()
