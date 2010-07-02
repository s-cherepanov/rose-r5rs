#ifndef __ROSE_GENERATOR_PROGRAM_HPP__
#define __ROSE_GENERATOR_PROGRAM_HPP__

#include "rose/ast/program.hpp"
#include "rose/generator/datum.hpp"
#include "rose/generator/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

using namespace rose;
using karma::grammar;
using karma::rule;

template<
    typename Iterator,
    typename Delimiter
>
struct expression :
    grammar<Iterator, ast_expression(), Delimiter>
{
    expression();

    rule<Iterator, ast_definition(), Delimiter> definition;

private:
    rose::generator::datum<Iterator, Delimiter> datum;

    rule<Iterator, ast_assignment(),        Delimiter> assignment;
    rule<Iterator, ast_body(),              Delimiter> body;
    rule<Iterator, ast_conditional(),       Delimiter> conditional;
    rule<Iterator, ast_expression(),        Delimiter> expression_;
    rule<Iterator, ast_expression(),        Delimiter> start;
    rule<Iterator, ast_lambda_expression(), Delimiter> lambda_expression;
    rule<Iterator, ast_procedure_call(),    Delimiter> procedure_call;
    rule<Iterator, ast_quotation(),         Delimiter> quotation;
    rule<Iterator, ast_variable(),          Delimiter> variable;

    typedef
        std::vector<ast_variable>
        formals_attr_type;

    rule<Iterator, formals_attr_type(), Delimiter> formals;

};  //  struct expression

template<
    typename Iterator,
    typename Delimiter
>
struct program :
    grammar<Iterator, ast_program(), Delimiter>
{
    program();

private:
    rose::generator::datum<Iterator, Delimiter> datum_;
    rose::generator::expression<Iterator, Delimiter> expression;

    rule<Iterator, ast_program(),    Delimiter> start;
    rule<Iterator, ast_expression(), Delimiter> command;
    rule<Iterator, ast_definition(), Delimiter> definition;

};  //  struct program

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_PROGRAM_HPP__
