#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"
#include "utilities.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(program_generator_suite)

void check_program(std::string const& input, std::string const& expected) {
    using namespace rose;

    namespace ascii = boost::spirit::ascii;
    namespace karma = boost::spirit::karma;
    namespace qi = boost::spirit::qi;

    using ascii::space;

    typedef
        parser::intertoken_space<std::string::const_iterator>
        skipper_type;

    typedef
        parser::r5rs_grammar<
            std::string::const_iterator,
            skipper_type
        >
        parser_type;

    typedef
        generator::program<
            std::back_insert_iterator<std::string>,
            ascii::space_type
        >
        generator_type;

    parser_type p;
    generator_type g;
    skipper_type skipper;

    ast_program attr;
    test_phrase_parser_attr(p, input, skipper, attr);
    std::string actual = test_generator_attr_delim(g, space, attr);
    BOOST_CHECK_EQUAL(actual, expected);
}

#define CHECK(source, expected) check_program(source, expected)

BOOST_AUTO_TEST_CASE(variable_test) {
    CHECK("x", "x ");
}

BOOST_AUTO_TEST_CASE(definition_test) {
    CHECK("(define x 1)", "( define x 1 ) ");
}

BOOST_AUTO_TEST_CASE(lambda_expression_test) {
    CHECK("(lambda (x) (* x 2))", "( lambda ( x ) ( * x 2 ) ) ");
    CHECK("(lambda (x)\n"
          "  (define y 2)\n"
          "  (* x y))",
          "( lambda ( x ) ( define y 2 ) ( * x y ) ) ");
}

BOOST_AUTO_TEST_CASE(definition_lambda_test) {
    CHECK("(define y (lambda (x) (* x 2)))",
          "( define y ( lambda ( x ) ( * x 2 ) ) ) ");
}

BOOST_AUTO_TEST_CASE(conditional_test) {
    CHECK("(if x 1 2)", "( if x 1 2 ) ");
    CHECK("(if x 1)", "( if x 1 ) ");
    CHECK("(if #t 1)", "( if #t 1 ) ");
}

BOOST_AUTO_TEST_CASE(assignment_test) {
    CHECK("(set! x 1)", "( set! x 1 ) ");
}

BOOST_AUTO_TEST_CASE(quotation_number_test) {
    CHECK("(quote 1)", "( quote 1 ) ");
}

BOOST_AUTO_TEST_CASE(quotation_boolean_test) {
    CHECK("(quote #t)", "( quote #t ) ");
    CHECK("(quote #f)", "( quote #f ) ");
}

BOOST_AUTO_TEST_CASE(quotation_symbol_test) {
    CHECK("(quote x)", "( quote x ) ");
}

BOOST_AUTO_TEST_CASE(quotation_abbrev_number_test) {
    CHECK("'1", "( quote 1 ) ");
}

BOOST_AUTO_TEST_SUITE_END()
