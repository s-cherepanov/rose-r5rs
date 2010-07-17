#ifndef __ROSE_PARSER_IMPL_LAMBDA_EXPRESSION_IPP__
#define __ROSE_PARSER_IMPL_LAMBDA_EXPRESSION_IPP__

#include "rose/parser/expression.hpp"
#include "rose/parser/lambda_expression.hpp"

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
lambda_expression<Iterator, Skipper>::
    lambda_expression(expression_type const* e)
:
    lambda_expression::base_type(start),
    expression_ptr(e),
    definition(e)
{
    using phoenix::at_c;
    using phoenix::push_back;
    using qi::_1;
    using qi::_val;
    using qi::no_case;

    start
        =   token.lparen
            >> no_case["lambda"]
            >> formals                      [at_c<0>(_val) = _1]
            >> body                         [at_c<1>(_val) = _1]
            >> token.rparen
        ;

    formals
        =   token.lparen
            >> *token.variable              [push_back(_val, _1)]
            >> token.rparen
        ;

    body
        =   *definition                     [push_back(at_c<0>(_val), _1)]
            >> sequence                     [at_c<1>(_val) = _1]
        ;

    sequence
        =   +command                        [push_back(_val, _1)]
        ;

    command
       %=   (*expression_ptr)
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_LAMBDA_EXPRESSION_IPP__

// vim:ft=cpp et
