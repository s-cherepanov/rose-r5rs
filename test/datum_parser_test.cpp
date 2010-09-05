#include "parsers.hpp"
#include "utilities.hpp"

#include <boost/assign.hpp>
#include <gtest/gtest.h>

using namespace boost::assign;
using namespace rose;

static void check(std::string const& input, ast_datum const& expected) {
    ast_datum actual;
    ASSERT_TRUE(test_phrase_parser_attr(
                datum_p, input, skipper_p, actual));
    ASSERT_TRUE(actual == expected);
}

TEST(datum_parser_test, parse_simple_datum) {
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

TEST(datum_parser_test, parse_empty_list) {
    ast_list list;
    check("()", ast_datum(list));
    check("( )", ast_datum(list));
    check(" ()", ast_datum(list));
    check("() ", ast_datum(list));
    check(" () ", ast_datum(list));
    check(" ( ) ", ast_datum(list));
}

TEST(datum_parser_test, parse_flat_list) {
    rose::ast_list list;
    list.elements += 1, 2, 3;
    check("(1 2 3)", ast_datum(list));
    check(" ( 1 2 3 ) ", ast_datum(list));
}

TEST(datum_parser_test, parse_mixed_list) {
    ast_list list;
    list.elements += 1, ast_symbol("x"), ast_string("hello");
    list.dotted_element.reset(true);
    check("(1 x \"hello\" . #t)", ast_datum(list));
}

TEST(datum_parser_test, parse_flat_vector) {
    ast_vector vec;
    vec += 1, 2, 3;
    check("#(1 2 3)", ast_datum(vec));
}

TEST(datum_parser_test, parse_mixed_vector) {
    ast_vector vec;
    vec += 1, ast_symbol("x"), ast_string("hello"), true;
    check("#(1 x \"hello\" #t)", ast_datum(vec));
}

TEST(datum_parser_test, parse_nested_vector) {
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
