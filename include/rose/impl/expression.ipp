#ifndef __ROSE_IMPL_EXPRESSION_IPP__
#define __ROSE_IMPL_EXPRESSION_IPP__

#include "rose/expression.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

template<
    typename Iterator,
    typename Skipper
>
expression<Iterator, Skipper>::expression() :
    expression::base_type( start )
{
    using qi::char_;
    using qi::lexeme;

    start
        =   variable
        |   literal
        ;

    variable
        =   lexeme[ identifier ]
        ;

    literal
        =   quotation
        |   self_evaluating
        ;

    self_evaluating
        =   lexeme[ boolean ]
        |   lexeme[ number ]
        |   lexeme[ character ]
        |   lexeme[ string ]
        ;

    quotation
        =   '\'' >> datum
        |   char_( '(' ) >> "quote" >> datum >> ')'
        ;

    start           .name( "expression" );
    variable        .name( "variable" );
    literal         .name( "literal" );
    self_evaluating .name( "self_evaluating" );
    quotation       .name( "quotation" );

    BOOST_SPIRIT_DEBUG_NODE( start );
    BOOST_SPIRIT_DEBUG_NODE( variable );
    BOOST_SPIRIT_DEBUG_NODE( literal );
    BOOST_SPIRIT_DEBUG_NODE( self_evaluating );
    BOOST_SPIRIT_DEBUG_NODE( quotation );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_EXPRESSION_IPP__
