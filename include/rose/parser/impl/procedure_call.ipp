#ifndef __ROSE_PARSER_IMPL_PROCEDURE_CALL_IPP__
#define __ROSE_PARSER_IMPL_PROCEDURE_CALL_IPP__

#include "rose/parser/procedure_call.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;

template<typename Iterator, typename Skipper>
procedure_call<Iterator, Skipper>::procedure_call(expression_type const* e) :
    procedure_call::base_type(start),
    expression_ptr(e)
{
    using phoenix::at_c;
    using phoenix::push_back;
    using qi::_1;
    using qi::_val;

    start
        =   procedure_call_.alias()
        ;

    procedure_call_
        =   token.lparen
            >> operator_                    [at_c<0>(_val) = _1]
            >> *operand                     [push_back(at_c<1>(_val), _1)]
            >> token.rparen
        ;

    operator_
        =   operand
        =   (*expression_ptr)
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_PROCEDURE_CALL_IPP__

// vim:ft=cpp et
