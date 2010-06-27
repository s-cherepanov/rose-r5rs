#ifndef __ROSE_GENERATOR_IMPL_PROGRAM_IPP__
#define __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

#include "rose/generator/attributes.hpp"
#include "rose/generator/program.hpp"

namespace rose {
namespace generator {

template<
    typename OutputIterator,
    typename Delimiter
>
expression<OutputIterator, Delimiter>::expression() :
    expression::base_type(start)
{
    using karma::lit;
    using karma::string;

    start
        =   expression_.alias()
        ;

    expression_
        =   datum
        |   variable
        |   quotation
        |   lambda_expression
        |   procedure_call
        |   conditional
        |   assignment
        ;

    variable
        =   karma::attr_cast(string)
        ;

    quotation
        =   lit('(') << "quote"
            << datum
            << ')'
        ;

    lambda_expression
        =   lit('(') << "lambda"
            << formals
            << body
            << ')'
        ;

    formals
        =   lit('(')
            << *variable
            << ')'
        ;

    body
        =   *definition
            << +expression_
        ;

    definition
        =   lit('(') << "define"
            << variable
            << expression_
            << ')'
        ;

    procedure_call
        =   lit('(')
            << expression_
            << *expression_
            << ')'
        ;

    conditional
        =   lit('(') << "if"
            << expression_
            << expression_
            << -expression_
            << ')'
        ;

    assignment
        =   lit('(') << "set!"
            << variable
            << expression_
            << ')'
        ;
}

template<
    typename OutputIterator,
    typename Delimiter
>
program<OutputIterator, Delimiter>::program() :
    program::base_type(start)
{
    start
        =   +(command | definition)
        ;

    command
        =   expression
        ;

    definition
        =   expression.definition
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

// vim:ft=cpp et
