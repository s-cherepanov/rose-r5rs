#ifndef __ROSE_EXPRESSION_HPP__
#define __ROSE_EXPRESSION_HPP__

#include "rose/ast/expression.hpp"
#include "rose/parser/token.hpp"
#include "rose/parser/datum.hpp"

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

    parser::token<Iterator, Skipper> token;
    parser::datum<Iterator, Skipper> datum;

    qi::rule<Iterator, ast::variable(),          Skipper> variable;
    qi::rule<Iterator, ast::expression(),        Skipper> literal;
    qi::rule<Iterator, ast::lambda_expression(), Skipper> lambda_expression;
    qi::rule<Iterator, ast::procedure_call(),    Skipper> procedure_call;
    qi::rule<Iterator, ast::conditional(),       Skipper> conditional;
    qi::rule<Iterator, ast::assignment(),        Skipper> assignment;
    qi::rule<Iterator, ast::definition(),        Skipper> definition;

private:
    typedef
        std::vector<ast::identifier>
        formals_attr_type;

    typedef
        std::vector<ast::expression>
        sequece_attr_type;

    qi::rule<Iterator, ast::expression(),   Skipper> start;
    qi::rule<Iterator, ast::expression(),   Skipper> expression_;
    qi::rule<Iterator, formals_attr_type(), Skipper> formals;
    qi::rule<Iterator, sequece_attr_type(), Skipper> sequence;
    qi::rule<Iterator, ast::body(),         Skipper> body;
    qi::rule<Iterator, ast::datum(),        Skipper> self_evaluating;
    qi::rule<Iterator, ast::quotation(),    Skipper> quotation;
    qi::rule<Iterator, ast::expression(),   Skipper> operator_;
    qi::rule<Iterator, ast::expression(),   Skipper> operand;
    qi::rule<Iterator, ast::expression(),   Skipper> command;
    qi::rule<Iterator, ast::expression(),   Skipper> test;
    qi::rule<Iterator, ast::expression(),   Skipper> consequent;
    qi::rule<Iterator, ast::expression(),   Skipper> alternate;

};  //  struct expression

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_EXPRESSION_HPP__
