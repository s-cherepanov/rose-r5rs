#include "generators.hpp"
#include "parsers.hpp"
#include "utilities.hpp"

#include <gtest/gtest.h>

using namespace rose;

static void check(std::string const& input, std::string const& expected) {
    ast_program attr;
    ASSERT_TRUE(test_phrase_parser_attr(program_p, input, skipper_p, attr));
    ASSERT_EQ(
            test_generator_attr_delim(
                program_g, delimiter_g, attr),
            expected);
}

TEST(program_generator_test, variable) {
    check("x", "x ");
}

TEST(program_generator_test, definition) {
    check("(define x 1)", "( define x 1 ) ");
}

TEST(program_generator_test, lambda_expression) {
    check(
            "(lambda (x) (* x 2))",
            "( lambda ( x ) ( * x 2 ) ) "
    );
}

TEST(program_generator_test, lambda_expression_with_definition) {
    check(
            "(lambda (x)\n"
            "  (define y 2)\n"
            "  (* x y))",

            "( lambda ( x ) ( define y 2 ) ( * x y ) ) "
    );
}

TEST(program_generator_test, definition_lambda) {
    check(
            "(define y (lambda (x) (* x 2)))",
            "( define y ( lambda ( x ) ( * x 2 ) ) ) "
    );
}

TEST(program_generator_test, conditional) {
    check("(if x 1 2)", "( if x 1 2 ) ");
    check("(if x 1)",   "( if x 1 ) ");
    check("(if #t 1)",  "( if #t 1 ) ");
}

TEST(program_generator_test, assignment) {
    check("(set! x 1)", "( set! x 1 ) ");
}

TEST(program_generator_test, quotation_number) {
    check("(quote 1)", "( quote 1 ) ");
}

TEST(program_generator_test, quotation_boolean) {
    check("(quote #t)", "( quote #t ) ");
    check("(quote #f)", "( quote #f ) ");
}

TEST(program_generator_test, quotation_symbol) {
    check("(quote x)", "( quote x ) ");
}

TEST(program_generator_test, quotation_abbrev_number) {
    check("'1", "( quote 1 ) ");
}
