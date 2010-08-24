#ifndef __ROSE_GENERATOR_IMPL_EXPRESSION_IPP__
#define __ROSE_GENERATOR_IMPL_EXPRESSION_IPP__

#include "rose/generator/expression.hpp"

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

template<
    typename Iterator,
    typename Delimiter
>
expression<Iterator, Delimiter>::expression() :
    expression::base_type(start)
{
    using karma::int_;
    using karma::lit;

    start
        =   expression_.alias()
        ;

    expression_
        =   boolean
        |   number
        |   character
        |   string
        |   variable
        |   quotation
        |   lambda_expression
        |   procedure_call
        |   conditional
        |   assignment
        ;

    variable
        =   karma::attr_cast(karma::string)
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

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_EXPRESSION_IPP__

// vim:ft=cpp et
