#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <gtest/gtest.h>

using namespace boost::assign;
using namespace rose;

template<typename Expression>
void check(std::string const& input, Expression const& expected) {
    ast_expression actual;
    ASSERT_TRUE(test_phrase_parser_attr(
                expression_p, input, skipper_p, actual));
    ASSERT_TRUE(actual == ast_expression(expected));
}

TEST(expression_parser_test, variable) {
    check("abc", ast_variable("abc"));
    check("+", ast_variable("+"));
    check("-", ast_variable("-"));
    check("a->b", ast_variable("a->b"));
    check("boolean?", ast_variable("boolean?"));
}

TEST(expression_parser_test, literal_quotation) {
    check("'a", ast_quotation(ast_datum(ast_symbol("a"))));

    ast_list list;
    list.elements += 1, 2, 3;
    check("'(1 2 3)", ast_quotation(ast_datum(list)));
    check("(quote (1 2 3))", ast_quotation(ast_datum(list)));
}

TEST(expression_parser_test, literal_self_evaluating_boolean) {
    check("#t", true);
    check("#f", false);
}

TEST(expression_parser_test, literal_self_evaluating_number) {
    check("10", 10);
    check("-10", -10);
    check("0", 0);
}

TEST(expression_parser_test, literal_self_evaluating_character) {
    check("#\\a", 'a');
    check("#\\newline", '\n');
    check("#\\space", ' ');
}

TEST(expression_parser_test, literal_self_evaluating_string) {
    check("\"\"", ast_string(""));
    check("\"\n\t\\\"\"", ast_string("\n\t\""));
    check("\"abc\"", ast_string("abc"));
}

TEST(expression_parser_test, procedure_call) {
    check(
            "(+ a b)",
            ast_procedure_call(
                ast_variable("+"),
                make_arguments(
                    ast_variable("a"),
                    ast_variable("b")))
    );

    check(
            "(symbol? 'a)",
            ast_procedure_call(
                ast_variable("symbol?"),
                make_arguments(ast_quotation(ast_symbol("a"))))
    );
}

TEST(expression_parser_test, conditional) {
    check("(if #t 1)", ast_conditional(true, 1));
    check("(if #t 1 2)", ast_conditional(true, 1, 2));
}

TEST(expression_parser_test, lambda_expression) {
    check(
            "(lambda () 1)",
            ast_lambda_expression(
                ast_formals(),
                ast_body(ast_definitions(), make_sequence(1)))
    );

    check(
            "(lambda (x) x)",
            ast_lambda_expression(
                ast_formals(make_formal_args(ast_variable("x"))),
                ast_body(make_sequence(ast_variable("x"))))
    );

    check(
            "(lambda (n . m) 10)",
            ast_lambda_expression(
                ast_formals(
                    make_formal_args(ast_variable("n")),
                    ast_variable("m")),
                ast_body(make_sequence(10)))
    );
}

TEST(expression_parser_test, factorial_lambda) {
    ast_lambda_expression inner_lambda(
            ast_formals(
                make_formal_args(ast_variable("m"))),
            ast_body(
                make_sequence(
                    ast_conditional(
                        ast_procedure_call(
                            ast_variable("<="),
                            make_arguments(ast_variable("m"), 0)),
                        1,
                        ast_procedure_call(
                            ast_variable("*"),
                            make_arguments(
                                ast_variable("m"), 
                                ast_procedure_call(
                                    ast_variable("factorial"),
                                    make_arguments(
                                        ast_procedure_call(
                                            ast_variable("-"),
                                            make_arguments(
                                                ast_variable("m"),
                                                1))))))))));

    ast_lambda_expression expected(
            ast_formals(make_formal_args(ast_variable("n"))),
            ast_body(
                make_definitions(
                    ast_definition(
                        ast_variable("factorial"),
                        inner_lambda)),
                make_sequence(
                    ast_procedure_call(
                        ast_variable("factorial"),
                        make_arguments(
                            ast_variable("n"))))));

    check(
            "(lambda (n)\n"
            "  (define factorial\n"
            "    (lambda (m)\n"
            "      (if (<= m 0)\n"
            "        1\n"
            "        (* m (factorial (- m 1))))))\n"
            "  (factorial n))",
            expected
    );
}
