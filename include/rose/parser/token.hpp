#ifndef __ROSE_TOKEN_HPP__
#define __ROSE_TOKEN_HPP__

#include "rose/ast/datum.hpp"
#include "rose/parser/boolean.hpp"
#include "rose/parser/character.hpp"
#include "rose/parser/identifier.hpp"
#include "rose/parser/number.hpp"
#include "rose/parser/string.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator, typename Skipper>
struct token :
    grammar<Iterator, Skipper>
{
    token();

    rule<Iterator, Skipper> start;
    rule<Iterator>          delimiter;

    rule<Iterator, ast_identifier(), Skipper> identifier;
    rule<Iterator, ast_string(),     Skipper> string;
    rule<Iterator, ast_variable(),   Skipper> variable;
    rule<Iterator, bool(),           Skipper> boolean;
    rule<Iterator, char(),           Skipper> character;
    rule<Iterator, int(),            Skipper> number;

    rule<Iterator, Skipper> lparen;
    rule<Iterator, Skipper> rparen;
    rule<Iterator, Skipper> sharp_lparen;
    rule<Iterator, Skipper> single_quote;
    rule<Iterator, Skipper> back_quote;
    rule<Iterator, Skipper> comma;
    rule<Iterator, Skipper> comma_at;
    rule<Iterator, Skipper> dot;

private:
    rose::parser::boolean<Iterator>    boolean_;
    rose::parser::character<Iterator>  character_;
    rose::parser::identifier<Iterator> identifier_;
    rose::parser::number<Iterator>     number_;
    rose::parser::string<Iterator>     string_;

    rule<Iterator, ast_variable()> variable_;

    rule<Iterator> expression_keyword;
    rule<Iterator> syntactic_keyword;

};  //  struct token

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_TOKEN_HPP__
