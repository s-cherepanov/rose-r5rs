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
program<OutputIterator, Delimiter>::program() :
    program::base_type(start)
{
    using karma::lit;
    using karma::string;

    start
        =   +(command | definition)
        ;

    command
        =   expression.alias()
        ;

    definition
        =   lit('(') << "define"
            << variable
            << expression
            << ')'
        ;

    variable
        =   karma::attr_cast(string)
        ;

    expression
        =   datum_
        |   variable
        |   quotation
        |   lambda_expression
        |   procedure_call
        |   conditional
        |   assignment
        ;

    quotation
        =   lit('(') << "quote"
            << datum_
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
            << +expression
        ;

    procedure_call
        =   lit('(')
            << expression
            << *expression
            << ')'
        ;

    conditional
        =   lit('(') << "if"
            << expression
            << expression
            << -expression
            << ')'
        ;

    assignment
        =   lit('(') << "set!"
            << variable
            << expression
            << ')'
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

// vim:ft=cpp et
