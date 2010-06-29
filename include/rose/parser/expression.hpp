#ifndef __ROSE_EXPRESSION_HPP__
#define __ROSE_EXPRESSION_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/datum.hpp"
#include "rose/parser/definition.hpp"
#include "rose/parser/lambda_expression.hpp"
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
struct expression :
    qi::grammar<Iterator, ast::expression(), Skipper>
{
    expression();

    rose::parser::datum<Iterator, Skipper>             datum;
	rose::parser::lambda_expression<Iterator, Skipper> lambda_expression;
	rose::parser::token<Iterator, Skipper>             token;

    qi::rule<Iterator, ast::variable(),       Skipper> variable;
    qi::rule<Iterator, ast::expression(),     Skipper> literal;
    qi::rule<Iterator, ast::procedure_call(), Skipper> procedure_call;
    qi::rule<Iterator, ast::conditional(),    Skipper> conditional;
    qi::rule<Iterator, ast::assignment(),     Skipper> assignment;

private:
    qi::rule<Iterator, ast::expression(),   Skipper> start;
    qi::rule<Iterator, ast::expression(),   Skipper> expression_;
    qi::rule<Iterator, ast::datum(),        Skipper> self_evaluating;
    qi::rule<Iterator, ast::quotation(),    Skipper> quotation;
    qi::rule<Iterator, ast::expression(),   Skipper> operator_;
    qi::rule<Iterator, ast::expression(),   Skipper> operand;
    qi::rule<Iterator, ast::expression(),   Skipper> test;
    qi::rule<Iterator, ast::expression(),   Skipper> consequent;
    qi::rule<Iterator, ast::expression(),   Skipper> alternate;

};  //  struct expression

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_EXPRESSION_HPP__
