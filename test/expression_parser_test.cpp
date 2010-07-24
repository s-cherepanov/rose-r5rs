#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(expression_suite)

using namespace boost::assign;
using namespace rose;

template<typename Expression>
void check(std::string const& input, Expression const& expected) {
    ast_expression actual;
    BOOST_CHECK(test_phrase_parser_attr(
                expression_p, input, skipper_p, actual));
    BOOST_CHECK(actual == ast_expression(expected));
}

BOOST_AUTO_TEST_CASE(variable_test) {
    check("abc", ast_variable("abc"));
    check("+", ast_variable("+"));
    check("-", ast_variable("-"));
    check("a->b", ast_variable("a->b"));
    check("boolean?", ast_variable("boolean?"));
}

BOOST_AUTO_TEST_CASE(literal_quotation_test) {
    check("'a", ast_quotation(ast_datum(ast_symbol("a"))));

    ast_list list;
    list.elements += 1, 2, 3;
    check("'(1 2 3)", ast_quotation(ast_datum(list)));
    check("(quote (1 2 3))", ast_quotation(ast_datum(list)));
}

BOOST_AUTO_TEST_CASE(literal_self_evaluating_boolean_test) {
    check("#t", true);
    check("#f", false);
}

BOOST_AUTO_TEST_CASE(literal_self_evaluating_number_test) {
    check("10", 10);
    check("-10", -10);
    check("0", 0);
}

BOOST_AUTO_TEST_CASE(literal_self_evaluating_character_test) {
    check("#\\a", 'a');
    check("#\\newline", '\n');
    check("#\\space", ' ');
}

BOOST_AUTO_TEST_CASE(literal_self_evaluating_string_test) {
    check("\"\"", ast_string(""));
    check("\"\n\t\\\"\"", ast_string("\n\t\""));
    check("\"abc\"", ast_string("abc"));
}

BOOST_AUTO_TEST_CASE(procedure_call_test) {
    {
        std::vector<ast_expression> args;
        args +=
            ast_expression(ast_variable("a")),
            ast_expression(ast_variable("b"));
        ast_procedure_call p(ast_expression(ast_variable("+")), args);
        check("(+ a b)", p);
    }

    {
        std::vector<ast_expression> args;
        args += ast_expression(ast_quotation(ast_datum(ast_symbol("a"))));
        ast_procedure_call p(ast_expression(ast_variable("symbol?")), args);
        check("(symbol? 'a)", p);
    }
}

BOOST_AUTO_TEST_CASE(conditional_test) {
    {
        ast_conditional c(true, 1);
        check("(if #t 1)", c);
    }

    {
        ast_conditional c(true, 1, 2);
        check("(if #t 1 2)", c);
    }
}

BOOST_AUTO_TEST_CASE(lambda_expression_test) {
    {
        ast_sequence sequence;
        sequence += 1;

        check("(lambda () 1)",
                ast_lambda_expression(
                    ast_formals(),
                    ast_body(ast_definitions(), sequence)));
    }

    {
        ast_formals formals;
        ast_sequence sequence;

        formals += ast_variable("x");
        sequence += ast_variable("x");

        check("(lambda (x) x)",
                ast_lambda_expression(formals, ast_body(sequence)));
    }

}

BOOST_AUTO_TEST_CASE(factorial_lambda_test) {
    ast_formals inner_formals;
    inner_formals += ast_variable("m");

    ast_arguments lte_args;
    lte_args += ast_variable("m"), 0;

    ast_arguments minus_args;
    minus_args += ast_variable("m"), 1;

    ast_arguments inner_factorial_args;
    inner_factorial_args +=
        ast_procedure_call(
                ast_variable("-"),
                minus_args);

    ast_procedure_call inner_factorial_call(
            ast_variable("factorial"),
            inner_factorial_args);

    ast_arguments mult_args;
    mult_args += ast_variable("m"), inner_factorial_call;

    ast_sequence inner_sequence;
    inner_sequence +=
        ast_conditional(
                ast_procedure_call(
                    ast_variable("<="),
                    lte_args),
                1,
                ast_procedure_call(
                    ast_variable("*"),
                    mult_args));

    ast_lambda_expression inner_lambda(
            inner_formals, ast_body(inner_sequence));

    ast_formals outer_formals;
    outer_formals += ast_variable("n");

    ast_definitions outer_definitions;
    outer_definitions +=
        ast_definition(
            ast_variable("factorial"),
            inner_lambda);

    ast_arguments outer_factorial_args;
    outer_factorial_args += ast_variable("n");

    ast_sequence outer_sequence;
    outer_sequence +=
        ast_procedure_call(
            ast_variable("factorial"),
            outer_factorial_args);

    ast_lambda_expression outer_lambda(
            outer_formals,
            ast_body(
                outer_definitions,
                outer_sequence));

    check(
            "(lambda (n)\n"
            "  (define factorial\n"
            "    (lambda (m)\n"
            "      (if (<= m 0)\n"
            "        1\n"
            "        (* m (factorial (- m 1))))))\n"
            "  (factorial n))",
            outer_lambda
    );
}

BOOST_AUTO_TEST_SUITE_END()
