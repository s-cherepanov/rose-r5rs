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
    typename OutputIterator,
    typename Delimiter
>
struct expression :
    grammar<OutputIterator, ast_expression(), Delimiter>
{
    expression();

    rule<OutputIterator, ast_definition(), Delimiter> definition;

private:
    rose::generator::datum<OutputIterator, Delimiter> datum;

    rule<OutputIterator, ast_assignment(),        Delimiter> assignment;
    rule<OutputIterator, ast_body(),              Delimiter> body;
    rule<OutputIterator, ast_conditional(),       Delimiter> conditional;
    rule<OutputIterator, ast_expression(),        Delimiter> expression_;
    rule<OutputIterator, ast_expression(),        Delimiter> start;
    rule<OutputIterator, ast_lambda_expression(), Delimiter> lambda_expression;
    rule<OutputIterator, ast_procedure_call(),    Delimiter> procedure_call;
    rule<OutputIterator, ast_quotation(),         Delimiter> quotation;
    rule<OutputIterator, ast_variable(),          Delimiter> variable;

    typedef
        std::vector<ast_variable>
        formals_attr_type;

    rule<OutputIterator, formals_attr_type(), Delimiter> formals;

};  //  struct expression

template<
    typename OutputIterator,
    typename Delimiter
>
struct program :
    grammar<OutputIterator, ast_program(), Delimiter>
{
    program();

private:
    rose::generator::datum<OutputIterator, Delimiter> datum_;
    rose::generator::expression<OutputIterator, Delimiter> expression;

    rule<OutputIterator, ast_program(),    Delimiter> start;
    rule<OutputIterator, ast_expression(), Delimiter> command;
    rule<OutputIterator, ast_definition(), Delimiter> definition;

};  //  struct program

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_PROGRAM_HPP__
