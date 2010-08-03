#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(program_parser_suite)

using namespace boost::assign;
using namespace rose;

void check(std::string const& input, ast_program const& expected) {
    ast_program actual;
    BOOST_CHECK(test_phrase_parser_attr(program_p, input, skipper_p, actual));
    BOOST_CHECK(actual == expected);
}

BOOST_AUTO_TEST_CASE(varaible_test) {
    ast_program expected;
    expected += ast_expression(ast_variable("x"));
    check("x", expected);
}

BOOST_AUTO_TEST_CASE(definition_test) {
    check(
            "(define x 1)\n"
            "(define y 2)\n",
            make_program(
                ast_definition(ast_variable("x"), 1),
                ast_definition(ast_variable("y"), 2))
    );
}

BOOST_AUTO_TEST_CASE(shebang_test) {
    check(
            "#!/usr/local/bin/rose\n"
            "\n"
            "1\n",
            make_program(ast_expression(1))
    );
}

BOOST_AUTO_TEST_CASE(call_factorial_test) {
    ast_program expected =
        make_program(
                ast_definition(
                    ast_variable("factorial"),
                    ast_lambda_expression(
                        make_formals(ast_variable("n")),
                        ast_body(
                            make_sequence(
                                ast_conditional(
                                    ast_procedure_call(
                                        ast_variable("<="),
                                        make_arguments(
                                            ast_variable("n"),
                                            0)),
                                    1,
                                    ast_procedure_call(
                                        ast_variable("*"),
                                        make_arguments(
                                            ast_variable("n"),
                                            ast_procedure_call(
                                                ast_variable("factorial"),
                                                make_arguments(
                                                    ast_procedure_call(
                                                        ast_variable("-"),
                                                        make_arguments(
                                                            ast_variable("n"),
                                                            1))))))))))),
                ast_procedure_call(
                        ast_variable("factorial"),
                        make_arguments(5)));

    check(
            "(define factorial\n"
            "  (lambda (n)\n"
            "    (if (<= n 0)\n"
            "      1\n"
            "      (* n (factorial (- n 1))))))\n"
            "\n"
            "(factorial 5)\n",
            expected
    );
}

BOOST_AUTO_TEST_SUITE_END()
