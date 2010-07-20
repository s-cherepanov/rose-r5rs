#ifndef __ROSE_PARSER_CONDITIONAL_HPP__
#define __ROSE_PARSER_CONDITIONAL_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<
    typename Iterator,
    typename Skipper
>
struct expression;

template<
    typename Iterator,
    typename Skipper
>
struct conditional :
    grammar<Iterator, ast_conditional(), Skipper>
{
    typedef
        rose::parser::expression<Iterator, Skipper>
        expression_type;

    conditional(expression_type const*);

private:
    expression_type const*                 expression_ptr;
    rose::parser::token<Iterator, Skipper> token;

    rule<Iterator, ast_conditional(), Skipper> start;
    rule<Iterator, ast_conditional(), Skipper> conditional_;
    rule<Iterator, ast_expression(),  Skipper> test;
    rule<Iterator, ast_expression(),  Skipper> consequent;
    rule<Iterator, ast_expression(),  Skipper> alternate;

};  //  struct conditional

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_CONDITIONAL_HPP__
