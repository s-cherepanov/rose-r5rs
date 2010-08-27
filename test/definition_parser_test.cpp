#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(definition_parser_suite)

using namespace rose;

void check(std::string const& input, ast_definition const& expected) {
    ast_definition actual;
    BOOST_CHECK(test_phrase_parser_attr(
                expression_p.lambda_expression.definition,
                input, skipper_p, actual));
    BOOST_CHECK(actual == expected);
}

BOOST_AUTO_TEST_CASE(simple_definition_test) {
    check(
            "(define x 1)",
            ast_definition(
                ast_variable("x"),
                ast_expression(1))
    );
}

BOOST_AUTO_TEST_CASE(lambda_define_test) {
    check(
            "(define x (lambda (n) n))",
            ast_definition(
                ast_variable("x"),
                ast_lambda_expression(
                    make_formals(ast_variable("n")),
                    ast_body(make_sequence(
                            ast_variable("n")))))
    );
}

BOOST_AUTO_TEST_CASE(lambda_define_abbrev_test) {
    check(
            "(define (x n) n)",
            ast_definition(
                ast_variable("x"),
                ast_lambda_expression(
                    make_formals(ast_variable("n")),
                    ast_body(make_sequence(
                            ast_variable("n")))))
    );
}

BOOST_AUTO_TEST_SUITE_END()
