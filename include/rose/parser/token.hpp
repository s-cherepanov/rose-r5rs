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

template<typename Iterator, typename Skipper>
struct token :
    qi::grammar<Iterator, Skipper>
{
    token();

    qi::rule<Iterator, Skipper> start;
    qi::rule<Iterator>          delimiter;

    qi::rule<Iterator, ast::identifier(), Skipper> identifier;
    qi::rule<Iterator, ast::string(),     Skipper> string;
    qi::rule<Iterator, ast::variable(),   Skipper> variable;
    qi::rule<Iterator, bool(),            Skipper> boolean;
    qi::rule<Iterator, char(),            Skipper> character;
    qi::rule<Iterator, int(),             Skipper> number;

    qi::rule<Iterator, Skipper> lparen;
    qi::rule<Iterator, Skipper> rparen;
    qi::rule<Iterator, Skipper> sharp_lparen;
    qi::rule<Iterator, Skipper> single_quote;
    qi::rule<Iterator, Skipper> back_quote;
    qi::rule<Iterator, Skipper> comma;
    qi::rule<Iterator, Skipper> comma_at;
    qi::rule<Iterator, Skipper> dot;

private:
    parser::boolean<Iterator>    boolean_;
    parser::character<Iterator>  character_;
    parser::identifier<Iterator> identifier_;
    parser::number<Iterator>     number_;
    parser::string<Iterator>     string_;

    qi::rule<Iterator, ast::variable()> variable_;

    qi::rule<Iterator> expression_keyword;
    qi::rule<Iterator> syntactic_keyword;

};  //  struct token

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_TOKEN_HPP__
