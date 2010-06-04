#ifndef __ROSE_EXPRESSION_HPP__
#define __ROSE_EXPRESSION_HPP__

#include "rose/ast/expression.hpp"
#include "rose/parser/token.hpp"
#include "rose/parser/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

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

    qi::rule<Iterator, ast::expression(),     Skipper> expression_;
    qi::rule<Iterator, ast::identifier(),     Skipper> variable;
    qi::rule<Iterator, ast::expression(),     Skipper> literal;
    qi::rule<Iterator, ast::datum(),          Skipper> self_evaluating;
    qi::rule<Iterator, ast::quotation(),      Skipper> quotation;
    qi::rule<Iterator, ast::procedure_call(), Skipper> procedure_call;
    qi::rule<Iterator, ast::expression(),     Skipper> operator_;
    qi::rule<Iterator, ast::expression(),     Skipper> operand;
    qi::rule<Iterator,                        Skipper> lambda_expression;
    qi::rule<Iterator,                        Skipper> formals;
    qi::rule<Iterator,                        Skipper> body;
    qi::rule<Iterator, ast::definition(),     Skipper> definition;
    qi::rule<Iterator,                        Skipper> procedure_def;
    qi::rule<Iterator,                        Skipper> def_formals;
    qi::rule<Iterator,                        Skipper> sequence;
    qi::rule<Iterator, ast::expression(),     Skipper> command;
    qi::rule<Iterator, ast::conditional(),    Skipper> conditional;
    qi::rule<Iterator, ast::expression(),     Skipper> test;
    qi::rule<Iterator, ast::expression(),     Skipper> consequent;
    qi::rule<Iterator, ast::expression(),     Skipper> alternate;
    qi::rule<Iterator, ast::assignment(),     Skipper> assignment;

};  //  struct expression

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_EXPRESSION_HPP__
