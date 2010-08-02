#ifndef __ROSE_IMPL_TOKEN_IPP__
#define __ROSE_IMPL_TOKEN_IPP__

#include "rose/parser/token.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

template<typename Iterator, typename Skipper>
token<Iterator, Skipper>::token() :
    token::base_type(start)
{
    using ascii::space;
    using qi::char_;
    using qi::eoi;
    using qi::lexeme;
    using qi::lit;
    using qi::no_case;

    start
        =   identifier
        |   boolean
        |   number
        |   character
        |   string
        |   lparen
        |   rparen
        |   sharp_lparen
        |   single_quote
        |   back_quote
        |   comma
        |   comma_at
        |   dot
        ;

    delimiter
        =   space | char_("()\";") | eoi
        ;

    expression_keyword
        =   no_case
            [   lit("if")   |   "lambda"    |   "quote"
            |   "set!"      |   "begin"     |   "cond"
            |   "and"       |   "or"        |   "case"
            |   "let"       |   "let*"      |   "letrec"
            |   "do"        |   "delay"     |   "quasiquote"
            ]
        ;

    syntactic_keyword
        =   no_case[lit("else") | "=>" | "define"]
        |   expression_keyword
        ;

    variable_
        =   identifier_ - syntactic_keyword
        ;

    identifier   = lexeme[identifier_ >> &delimiter];
    variable     = lexeme[variable_   >> &delimiter];
    number       = lexeme[number_     >> &delimiter];
    character    = lexeme[character_  >> &delimiter];
    dot          = lexeme['.'         >> &delimiter];
    boolean      = lexeme[boolean_];
    string       = lexeme[string_];
    lparen       = lexeme['(' ];
    rparen       = lexeme[')' ];
    sharp_lparen = lexeme["#("];
    single_quote = lexeme['\''];
    back_quote   = lexeme['`'];
    comma        = lexeme[','];
    comma_at     = lexeme[",@"];
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_TOKEN_IPP__

// vim:ft=cpp et
