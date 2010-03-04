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
    expression::base_type( expression_ )
{
    using qi::char_;
    using qi::lexeme;

    expression_
        =   variable
        |   literal
        |   procedure_call
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

    procedure_call
        =   '(' >> operator_ >> *operand >> ')'
        ;

    operator_
        =   expression_.alias()
        ;

    operand
        =   expression_.alias()
        ;

    expression_         .name( "expression" );
    variable            .name( "variable" );
    literal             .name( "literal" );
    self_evaluating     .name( "self_evaluating" );
    quotation           .name( "quotation" );
    procedure_call      .name( "procedure_call" );
    operator_           .name( "operator" );
    operand             .name( "operand" );
    lambda_expression   .name( "lambda_expression" );

    BOOST_SPIRIT_DEBUG_NODE( expression_ );
    BOOST_SPIRIT_DEBUG_NODE( variable );
    BOOST_SPIRIT_DEBUG_NODE( literal );
    BOOST_SPIRIT_DEBUG_NODE( self_evaluating );
    BOOST_SPIRIT_DEBUG_NODE( quotation );
    BOOST_SPIRIT_DEBUG_NODE( procedure_call );
    BOOST_SPIRIT_DEBUG_NODE( operator_ );
    BOOST_SPIRIT_DEBUG_NODE( operand );
    BOOST_SPIRIT_DEBUG_NODE( lambda_expression );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_EXPRESSION_IPP__
