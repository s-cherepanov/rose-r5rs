#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <gtest/gtest.h>

using namespace rose;

static void check(std::string const& input, ast_definition const& expected) {
    ast_definition actual;
    ASSERT_TRUE(test_phrase_parser_attr(
                expression_p.lambda_expression.definition,
                input, skipper_p, actual));
    ASSERT_TRUE(actual == expected);
}

TEST(definition_parser_test, simple_definition) {
    check(
            "(define x 1)",
            ast_definition(
                ast_variable("x"),
                ast_expression(1))
    );
}

TEST(definition_parser_test, lambda_definition) {
    check(
            "(define x (lambda (n) n))",
            ast_definition(
                ast_variable("x"),
                ast_lambda_expression(
                    ast_formals(make_formal_args(ast_variable("n"))),
                    ast_body(make_sequence(
                            ast_variable("n")))))
    );
}

TEST(definition_parser_test, lambda_definition_with_rest_list_only) {
    check(
            "(define x (lambda n n))",
            ast_definition(
                ast_variable("x"),
                ast_lambda_expression(
                    ast_formals(
                        ast_formal_args(),
                        ast_variable("n")),
                    ast_body(make_sequence(
                            ast_variable("n")))))
    );
}

TEST(definition_parser_test, abbrev_lambda_definition) {
    check(
            "(define (x n) n)",
            ast_definition(
                ast_variable("x"),
                ast_lambda_expression(
                    ast_formals(make_formal_args(ast_variable("n"))),
                    ast_body(make_sequence(
                            ast_variable("n")))))
    );
}

TEST(definition_parser_test, abbrev_lambda_definition_with_rest_list) {
    check(
            "(define (x n . m) n)",
            ast_definition(
                ast_variable("x"),
                ast_lambda_expression(
                    ast_formals(
                        make_formal_args(ast_variable("n")),
                        ast_variable("m")),
                    ast_body(make_sequence(
                            ast_variable("n")))))
    );
}
