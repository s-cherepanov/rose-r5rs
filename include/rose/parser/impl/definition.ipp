#ifndef __ROSE_PARSER_IMPL_DEFINITION_IPP__
#define __ROSE_PARSER_IMPL_DEFINITION_IPP__

#include "rose/parser/definition.hpp"
#include "rose/parser/expression.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;

template<
    typename Iterator,
    typename Skipper
>
definition<Iterator, Skipper>::
    definition(expression_type const* e)
:
    definition::base_type(start),
    expression_ptr(e)
{
    using phoenix::at_c;
    using qi::_1;
    using qi::_val;
    using qi::no_case;

    start
        =   token.lparen
            >> no_case["define"]
            >> token.variable               [at_c<0>(_val) = _1]
            >> (*expression_ptr)            [at_c<1>(_val) = _1]
            >> token.rparen
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_DEFINITION_IPP__

// vim:ft=cpp et
