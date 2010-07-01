#ifndef __ROSE_IMPL_EXPRESSION_IPP__
#define __ROSE_IMPL_EXPRESSION_IPP__

#include "rose/parser/expression.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

template<
    typename Iterator,
    typename Skipper
>
expression<Iterator, Skipper>::expression() :
    expression::base_type(start),
    lambda_expression(this)
{
    using qi::char_;
    using qi::no_case;

    using namespace qi::labels;

    using phoenix::at_c;
    using phoenix::push_back;

    start
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

    expression_
        =   start.alias()
        ;

    quotation
        =   token.single_quote
            >> datum                        [_val = _1]
        |   token.lparen
            >> no_case["quote"]
            >> datum                        [_val = _1]
            >> token.rparen
        ;

    procedure_call
        =   token.lparen
            >> operator_                    [at_c<0>(_val) = _1]
            >> *operand                     [push_back(at_c<1>(_val), _1)]
            >> token.rparen
        ;

    operator_
        =   operand
        =   expression_.alias()
        ;

    conditional
        =   token.lparen
            >> no_case["if"]
            >> test                         [at_c<0>(_val) = _1]
            >> consequent                   [at_c<1>(_val) = _1]
            >> -alternate                   [at_c<2>(_val) = _1]
            >> token.rparen
        ;

    test
        =   consequent
        =   alternate
        =   expression_.alias()
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
