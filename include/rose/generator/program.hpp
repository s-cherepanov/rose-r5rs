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
struct program :
    karma::grammar<OutputIterator, ast::program(), Delimiter>
{
    program();

private:
    generator::datum<OutputIterator, Delimiter> datum_;

    rule<OutputIterator, ast::program(),           Delimiter> start;
    rule<OutputIterator, ast::expression(),        Delimiter> command;
    rule<OutputIterator, ast::definition(),        Delimiter> definition;
    rule<OutputIterator, ast::expression(),        Delimiter> expression;
    rule<OutputIterator, ast::quotation(),         Delimiter> quotation;
    rule<OutputIterator, ast::lambda_expression(), Delimiter> lambda_expression;
    rule<OutputIterator, ast::procedure_call(),    Delimiter> procedure_call;
    rule<OutputIterator, ast::conditional(),       Delimiter> conditional;
    rule<OutputIterator, ast::assignment(),        Delimiter> assignment;
    rule<OutputIterator, ast::variable(),          Delimiter> variable;
    rule<OutputIterator, ast::symbol(),            Delimiter> symbol;
    rule<OutputIterator, ast::identifier(),        Delimiter> identifier;
    rule<OutputIterator, ast::body(),              Delimiter> body;

    typedef
        std::vector<ast::variable>
        formals_attr_type;

    rule<OutputIterator, formals_attr_type(), Delimiter> formals;

};  //  struct program

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_PROGRAM_HPP__
