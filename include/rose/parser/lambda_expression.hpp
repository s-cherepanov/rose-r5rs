#ifndef __ROSE_PARSER_LAMBDA_EXPRESSION_HPP__
#define __ROSE_PARSER_LAMBDA_EXPRESSION_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/definition.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using namespace rose;
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
struct lambda_expression :
    grammar<Iterator, ast_lambda_expression(), Skipper>
{
    typedef
        rose::parser::expression<Iterator, Skipper>
        expression_type;

    lambda_expression(expression_type const*);

private:
    expression_type const*                      expression_ptr;
	rose::parser::definition<Iterator, Skipper> definition;
	rose::parser::token<Iterator, Skipper>      token;

    rule<Iterator, ast_lambda_expression(), Skipper> start;
    rule<Iterator, ast_formals(),           Skipper> formals;
    rule<Iterator, ast_sequence(),          Skipper> sequence;
    rule<Iterator, ast_body(),              Skipper> body;
    rule<Iterator, ast_expression(),        Skipper> command;

};  //  struct lambda_expression

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_LAMBDA_EXPRESSION_HPP__
