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

// BOOST_AUTO_TEST_CASE(procedure_call_ast_test) {
//     ast_expression op(ast_variable("+"));
//     std::vector<ast_expression> args;
// 
//     args.push_back(ast_expression(1));
//     args.push_back(ast_expression(2));
// 
//     ast_expression e(ast_procedure_call(op, args));
//     BOOST_CHECK(test_expression_ast("(+ 1 2)", e));
// }
// 
// BOOST_AUTO_TEST_CASE(conditional_test) {
//     BOOST_CHECK(is_expression("(if #t 1)"));
//     BOOST_CHECK(is_expression("(if #t 1 2)"));
// }
// 
// BOOST_AUTO_TEST_CASE(lambda_expression_test) {
//     BOOST_CHECK(is_expression("(lambda (x) (+ x 1))"));
//     BOOST_CHECK(is_expression("(lambda () 1)"));
//     BOOST_CHECK(is_expression("(lambda (x y) (+ x 1))"));
// }

BOOST_AUTO_TEST_SUITE_END()
