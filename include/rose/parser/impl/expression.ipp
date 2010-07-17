#ifndef __ROSE_IMPL_EXPRESSION_IPP__
#define __ROSE_IMPL_EXPRESSION_IPP__

#include "rose/parser/expression.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
expression<Iterator, Skipper>::expression() :
    expression::base_type(start),
    conditional(this),
    lambda_expression(this),
    procedure_call(this)
{
    using qi::_1;
    using qi::_val;
    using qi::no_case;

    start
        =   expression_.alias()
        ;

    expression_
       %=   token.boolean
        |   token.number
        |   token.character
        |   token.string
        |   token.variable
        |   quotation
        |   lambda_expression
        |   procedure_call
        |   conditional
        |   assignment
        ;

    quotation
        =   token.single_quote
            >> datum                        [_val = _1]
        |   token.lparen
            >> no_case["quote"]
            >> datum                        [_val = _1]
            >> token.rparen
        ;

    assignment
        =   token.lparen
            >> no_case["set!"]
            >> token.variable
            >> expression_
            >> token.rparen
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_EXPRESSION_IPP__

// vim:ft=cpp et
