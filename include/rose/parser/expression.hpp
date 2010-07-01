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

namespace qi = boost::spirit::qi;

using namespace rose;
using qi::grammar;
using qi::rule;

template<
    typename Iterator,
    typename Skipper
>
struct expression :
    grammar<Iterator, ast_expression(), Skipper>
{
    expression();

private:
    rose::parser::datum<Iterator, Skipper>             datum;
	rose::parser::lambda_expression<Iterator, Skipper> lambda_expression;
	rose::parser::token<Iterator, Skipper>             token;

    rule<Iterator, ast_expression(),     Skipper> start;
    rule<Iterator, ast_expression(),     Skipper> expression_;
    rule<Iterator, ast_procedure_call(), Skipper> procedure_call;
    rule<Iterator, ast_conditional(),    Skipper> conditional;
    rule<Iterator, ast_assignment(),     Skipper> assignment;
    rule<Iterator, ast_quotation(),      Skipper> quotation;
    rule<Iterator, ast_expression(),     Skipper> operator_;
    rule<Iterator, ast_expression(),     Skipper> operand;
    rule<Iterator, ast_expression(),     Skipper> test;
    rule<Iterator, ast_expression(),     Skipper> consequent;
    rule<Iterator, ast_expression(),     Skipper> alternate;

};  //  struct expression

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_EXPRESSION_HPP__
