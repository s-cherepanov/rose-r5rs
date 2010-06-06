#ifndef __ROSE_IMPL_TOKEN_IPP__
#define __ROSE_IMPL_TOKEN_IPP__

#include "rose/parser/token.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator, typename Skipper>
token<Iterator, Skipper>::token() :
    token::base_type(start)
{
    using ascii::graph;
    using ascii::space;
    using qi::attr;
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

    boolean_
        =   no_case
            [
                "#t" >> attr(true)
            |   "#f" >> attr(false)
            ]
        ;

    string_
        =   '"' >> *(string_element - '"') >> '"'
        ;

    string_element
        =   ((graph | space) - char_("\"\\"))
        |   lit("\\\"") >> attr('"')
        |   lit("\\\\") >> attr('\\')
        |   lit("\\n")  >> attr('\n')
        |   lit("\\t")  >> attr('\t')
        ;

    expression_keyword
        =   lit("quote") | "lambda" | "if" | "set!" | "begin" | "cond" |
            "and" | "or" | "case" | "let" | "let*" | "letrec" | "do" |
            "delay" | "quasiquote"
        ;

    syntactic_keyword
        =   expression_keyword | "else " | "=>" | "define"
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

    back_quote  .name("back_quote");
    boolean     .name("boolean");
    character   .name("character");
    comma_at    .name("comma_at");
    comma       .name("comma");
    dot         .name("dot");
    identifier  .name("identifier");
    lparen      .name("lparen");
    number      .name("number");
    rparen      .name("rparen");
    sharp_lparen.name("sharp_lparen");
    single_quote.name("single_quote");
    string      .name("string");
    variable    .name("variable");
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_TOKEN_IPP__

// vim:ft=cpp et
