#ifndef __ROSE_PARSER_IMPL_CONDITIONAL_IPP__
#define __ROSE_PARSER_IMPL_CONDITIONAL_IPP__

#include "rose/parser/conditional.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;

template<typename Iterator, typename Skipper>
conditional<Iterator, Skipper>::conditional(expression_type const* e) :
    conditional::base_type(start),
    expression_ptr(e)
{
    using phoenix::at_c;
    using qi::_1;
    using qi::_val;
    using qi::no_case;

    start
        =   conditional_.alias()
        ;

    conditional_
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
        =   (*expression_ptr)
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_CONDITIONAL_IPP__

// vim:ft=cpp et
