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

template<typename Iterator, typename Skipper>
lambda_expression<Iterator, Skipper>::
    lambda_expression(expression_type const* e)
:
    lambda_expression::base_type(start),
    definition(e),
    expression_ptr(e)
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
            >> *token.variable              [push_back(at_c<0>(_val), _1)]
            >> token.rparen
        |   token.variable                  [at_c<1>(_val) = _1]
        |   token.lparen
            >> +token.variable
            >> -(token.dot
                 >> token.variable          [at_c<1>(_val) = _1])
            >> token.rparen
        ;

    body
        =   *definition                     [push_back(at_c<0>(_val), _1)]
            >> sequence                     [at_c<1>(_val) = _1]
        ;

    sequence
        =   +(*expression_ptr)              [push_back(_val, _1)]
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_LAMBDA_EXPRESSION_IPP__

// vim:ft=cpp et
