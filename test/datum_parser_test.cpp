#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(datum_suite)

using namespace boost::assign;
using namespace rose;

void check(std::string const& input, ast_datum const& expected) {
    ast_datum actual;
    BOOST_CHECK(test_phrase_parser_attr(
                datum_p, input, skipper_p, actual));
    BOOST_CHECK_EQUAL(actual, expected);
}

BOOST_AUTO_TEST_CASE(simple_datum_test) {
    // boolean
    check("#t", ast_datum(true));
    check("#f", ast_datum(false));

    // number
    check("10", ast_datum(10));
    check("-10", ast_datum(-10));
    check("0", ast_datum(0));

    // character
    check("#\\a", ast_datum('a'));
    check("#\\space", ast_datum(' '));
    check("#\\newline", ast_datum('\n'));

    // string
    check("\"hello\nworld\t!\"",
            ast_datum(ast_string("hello\nworld\t!")));

    // symbol
    check("hello", ast_datum(ast_symbol("hello")));
    check("+", ast_datum(ast_symbol("+")));
    check("-", ast_datum(ast_symbol("-")));
    check("...", ast_datum(ast_symbol("...")));
    check("list->string", ast_datum(ast_symbol("list->string")));
}

BOOST_AUTO_TEST_CASE(empty_list_test) {
    ast_list list;
    check("()", ast_datum(list));
    check("( )", ast_datum(list));
    check(" ()", ast_datum(list));
    check("() ", ast_datum(list));
    check(" () ", ast_datum(list));
    check(" ( ) ", ast_datum(list));
}

BOOST_AUTO_TEST_CASE(flat_list_test) {
    rose::ast_list list;
    list.elements += 1, 2, 3;
    check("(1 2 3)", ast_datum(list));
    check(" ( 1 2 3 ) ", ast_datum(list));
}

BOOST_AUTO_TEST_CASE(mixed_list_test) {
    ast_list list;
    list.elements += 1, ast_symbol("x"), ast_string("hello");
    list.dotted_element.reset(true);
    check("(1 x \"hello\" . #t)", ast_datum(list));
}

BOOST_AUTO_TEST_CASE(flat_vector_test) {
    ast_vector vec;
    vec += 1, 2, 3;
    check("#(1 2 3)", ast_datum(vec));
}

BOOST_AUTO_TEST_CASE(mixed_vector_test) {
    ast_vector vec;
    vec += 1, ast_symbol("x"), ast_string("hello"), true;
    check("#(1 x \"hello\" #t)", ast_datum(vec));
}

BOOST_AUTO_TEST_CASE(nested_vector_test) {
    {
        ast_vector vec, empty;
        empty += empty;
        vec += empty;
        check("#(#(#()))", ast_datum(vec));
    }

    {
        ast_vector in, out;
        in += ast_string("hello"), ast_vector(), ast_string("world");
        out += 1, in, true;
        check("#(1 #(\"hello\" #() \"world\") #t)", ast_datum(out));
    }

    {
        ast_list list;
        list.elements += 1, 2, 3;
        list.dotted_element.reset(4);

        ast_vector vec;
        vec += true, list, ast_string("abc");

        check("#(#t (1 2 3 . 4) \"abc\")", ast_datum(vec));
    }
}

BOOST_AUTO_TEST_SUITE_END()
