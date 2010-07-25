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
    ast_lambda_expression inner_lambda(
            make_formals(
                ast_variable("m")),
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
            make_formals(ast_variable("n")),
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

BOOST_AUTO_TEST_SUITE_END()
