#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <gtest/gtest.h>

using namespace boost::assign;
using namespace rose;

static void check(std::string const& input, ast_program const& expected) {
    ast_program actual;
    ASSERT_TRUE(test_phrase_parser_attr(program_p, input, skipper_p, actual));
    ASSERT_TRUE(actual == expected);
}

TEST(program_parser_test, varaible) {
    ast_program expected;
    expected += ast_expression(ast_variable("x"));
    check("x", expected);
}

TEST(program_parser_test, definition) {
    check(
            "(define x 1)\n"
            "(define y 2)\n",
            make_program(
                ast_definition(ast_variable("x"), 1),
                ast_definition(ast_variable("y"), 2))
    );
}

TEST(program_parser_test, shebang) {
    check(
            "#!/usr/local/bin/rose\n"
            "\n"
            "1\n",
            make_program(ast_expression(1))
    );
}

TEST(program_parser_test, call_factorial) {
    ast_program expected =
        make_program(
                ast_definition(
                    ast_variable("factorial"),
                    ast_lambda_expression(
                        ast_formals(make_formal_args(ast_variable("n"))),
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
            "(define (factorial n)\n"
            "  (if (<= n 0)\n"
            "    1\n"
            "    (* n (factorial (- n 1)))))\n"
            "\n"
            "(factorial 5)\n",
            expected
    );
}
