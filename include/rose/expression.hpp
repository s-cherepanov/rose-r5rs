#ifndef __ROSE_EXPRESSION_HPP__
#define __ROSE_EXPRESSION_HPP__

#include "rose/token.hpp"
#include "rose/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct expression :
    qi::grammar<Iterator, Skipper>
{
    expression();

    rose::token<Iterator, Skipper> token;
    rose::datum<Iterator, Skipper> datum;

    qi::rule<Iterator, Skipper> expression_;
    qi::rule<Iterator, Skipper> variable;
    qi::rule<Iterator, Skipper> literal;
    qi::rule<Iterator, Skipper> self_evaluating;
    qi::rule<Iterator, Skipper> quotation;
    qi::rule<Iterator, Skipper> procedure_call;
    qi::rule<Iterator, Skipper> operator_;
    qi::rule<Iterator, Skipper> operand;
    qi::rule<Iterator, Skipper> lambda_expression;
    qi::rule<Iterator, Skipper> formals;
    qi::rule<Iterator, Skipper> body;
    qi::rule<Iterator, Skipper> definition;
    qi::rule<Iterator, Skipper> def_formals;
    qi::rule<Iterator, Skipper> sequence;
    qi::rule<Iterator, Skipper> command;
    qi::rule<Iterator, Skipper> conditional;
    qi::rule<Iterator, Skipper> test;
    qi::rule<Iterator, Skipper> consequent;
    qi::rule<Iterator, Skipper> alternate;
    qi::rule<Iterator, Skipper> assignment;

};  //  struct expression

}   //  namespace rose

#endif  //  __ROSE_EXPRESSION_HPP__
