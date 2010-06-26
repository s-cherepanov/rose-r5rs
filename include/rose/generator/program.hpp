#ifndef __ROSE_GENERATOR_PROGRAM_HPP__
#define __ROSE_GENERATOR_PROGRAM_HPP__

#include "rose/ast/program.hpp"
#include "rose/generator/datum.hpp"
#include "rose/generator/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace ast = rose::ast;
namespace karma = boost::spirit::karma;

using karma::rule;

template<
    typename OutputIterator,
    typename Delimiter
>
struct expression :
    karma::grammar<OutputIterator, ast::expression(), Delimiter>
{
    expression();

    rule<OutputIterator, ast::definition(), Delimiter> definition;

private:
    rose::generator::datum<OutputIterator, Delimiter> datum;

    rule<OutputIterator, ast::expression(),        Delimiter> start;
    rule<OutputIterator, ast::quotation(),         Delimiter> quotation;
    rule<OutputIterator, ast::lambda_expression(), Delimiter> lambda_expression;
    rule<OutputIterator, ast::procedure_call(),    Delimiter> procedure_call;
    rule<OutputIterator, ast::conditional(),       Delimiter> conditional;
    rule<OutputIterator, ast::assignment(),        Delimiter> assignment;
    rule<OutputIterator, ast::body(),              Delimiter> body;
    rule<OutputIterator, ast::variable(),          Delimiter> variable;

    typedef
        std::vector<ast::variable>
        formals_attr_type;

    rule<OutputIterator, formals_attr_type(), Delimiter> formals;

};  //  struct expression

template<
    typename OutputIterator,
    typename Delimiter
>
struct program :
    karma::grammar<OutputIterator, ast::program(), Delimiter>
{
    program();

private:
    rose::generator::datum<OutputIterator, Delimiter> datum_;
    rose::generator::expression<OutputIterator, Delimiter> expression;

    rule<OutputIterator, ast::program(),    Delimiter> start;
    rule<OutputIterator, ast::expression(), Delimiter> command;
    rule<OutputIterator, ast::definition(), Delimiter> definition;

};  //  struct program

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_PROGRAM_HPP__
