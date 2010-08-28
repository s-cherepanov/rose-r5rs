#ifndef __ROSE_PARSER_IMPL_DEFINITION_IPP__
#define __ROSE_PARSER_IMPL_DEFINITION_IPP__

#include "rose/parser/definition.hpp"
#include "rose/parser/expression.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;

template<typename Iterator, typename Skipper>
definition<Iterator, Skipper>::definition(expression_type const* e) :
    definition::base_type(start),
    expression_ptr(e)
{
    using phoenix::at_c;
    using phoenix::construct;
    using phoenix::push_back;
    using qi::_1;
    using qi::_a;
    using qi::_b;
    using qi::_val;
    using qi::no_case;

    start
        =   plain_definition
        |   procedure_definition
        ;

    plain_definition
        =   token.lparen
            >> no_case["define"]
            >> token.variable               [at_c<0>(_val) = _1]
            >> (*expression_ptr)            [at_c<1>(_val) = _1]
            >> token.rparen
        ;

    typedef
        ast_lambda_expression
        lambda_type;

    procedure_definition
        =   (token.lparen
            >> no_case["define"]
            >> token.lparen
            >> token.variable               [at_c<0>(_val) = _1]
            >> def_formals                  [_a = _1]
            >> token.rparen
            >> body                         [_b = _1]
            >> token.rparen)                [at_c<1>(_val) =
                                             construct<lambda_type>(_a, _b)]
        ;

    def_formals
        =   *token.variable                 [push_back(at_c<0>(_val), _1)]
            >> -(token.dot
                 >> token.variable          [at_c<1>(_val) = _1])
        ;

    body
        =   *start                          [push_back(at_c<0>(_val), _1)]
            >> sequence                     [at_c<1>(_val) = _1]
        ;

    sequence
        =   +(*expression_ptr)              [push_back(_val, _1)]
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_DEFINITION_IPP__

// vim:ft=cpp et
