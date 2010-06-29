#ifndef __ROSE_PARSER_LAMBDA_EXPRESSION_HPP__
#define __ROSE_PARSER_LAMBDA_EXPRESSION_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/definition.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace ast = rose::ast;
namespace qi = boost::spirit::qi;

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
    qi::grammar<Iterator, ast::lambda_expression(), Skipper>
{
    typedef
        rose::parser::expression<Iterator, Skipper>
        expression_type;

    lambda_expression(expression_type const*);

private:
    expression_type const*                      expression_ptr;
	rose::parser::definition<Iterator, Skipper> definition;
	rose::parser::token<Iterator, Skipper>      token;

    qi::rule<Iterator, ast::lambda_expression(), Skipper> start;
    qi::rule<Iterator, ast::formals(),           Skipper> formals;
    qi::rule<Iterator, ast::sequence(),          Skipper> sequence;
    qi::rule<Iterator, ast::body(),              Skipper> body;
    qi::rule<Iterator, ast::expression(),        Skipper> command;

};  //  struct lambda_expression

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_LAMBDA_EXPRESSION_HPP__
