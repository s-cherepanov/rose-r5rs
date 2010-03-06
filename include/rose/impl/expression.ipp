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

    expression_
        =   variable
        |   literal
        |   procedure_call
        |   lambda_expression
        |   conditional
        |   assignment
        ;

    variable
        =   token.identifier
        ;

    literal
        =   quotation
        |   self_evaluating
        ;

    self_evaluating
        =   token.boolean
        |   token.number
        |   token.character
        |   token.string
        ;

    quotation
        =   token.single_quote >> datum
        |   token.lparen
            >> "quote" >> datum
            >> token.rparen
        ;

    procedure_call
        =   token.lparen
            >> operator_ >> *operand
            >> token.rparen
        ;

    operator_
        =   expression_.alias()
        ;

    operand
        =   expression_.alias()
        ;

    lambda_expression
        =   token.lparen
            >>  "lambda" >> formals >> body
            >>  token.rparen
        ;

    formals
        =   token.lparen >> *variable >> token.rparen
        |   variable
        |   token.lparen
            >>  +variable >> token.dot >> variable
            >>  token.rparen
        ;

    body
        =   *definition >> sequence
        ;

    definition
        =   token.lparen
            >>  "define" >> variable >> expression_
            >>  token.rparen
        |   token.lparen >> "define"
            >>  token.lparen
            >>  variable >> def_formals
            >>  token.rparen
            >>  body >> token.rparen
        ;

    sequence
        =   *command >> expression_
        ;

    command
        =   expression_.alias()
        ;

    conditional
        =   token.lparen
            >>  "if" >> test >> consequent >> -alternate
            >>  token.rparen
        ;

    test
        =   expression_.alias()
        ;

    consequent
        =   expression_.alias()
        ;

    alternate
        =   expression_.alias()
        ;

    assignment
        =   token.lparen
            >>  "set!" >> variable >> expression_
            >>  token.rparen
        ;

    expression_      .name( "expression" );
    variable         .name( "variable" );
    literal          .name( "literal" );
    self_evaluating  .name( "self_evaluating" );
    quotation        .name( "quotation" );
    procedure_call   .name( "procedure_call" );
    operator_        .name( "operator" );
    operand          .name( "operand" );
    lambda_expression.name( "lambda_expression" );
    formals          .name( "formals" );
    body             .name( "body" );
    sequence         .name( "sequence" );
    command          .name( "command" );
    conditional      .name( "conditional" );
    test             .name( "test" );
    consequent       .name( "consequent" );
    alternate        .name( "alternate" );
    assignment       .name( "assignment" );

    BOOST_SPIRIT_DEBUG_NODE( expression_ );
    BOOST_SPIRIT_DEBUG_NODE( variable );
    BOOST_SPIRIT_DEBUG_NODE( literal );
    BOOST_SPIRIT_DEBUG_NODE( self_evaluating );
    BOOST_SPIRIT_DEBUG_NODE( quotation );
    BOOST_SPIRIT_DEBUG_NODE( procedure_call );
    BOOST_SPIRIT_DEBUG_NODE( operator_ );
    BOOST_SPIRIT_DEBUG_NODE( operand );
    BOOST_SPIRIT_DEBUG_NODE( lambda_expression );
    BOOST_SPIRIT_DEBUG_NODE( formals );
    BOOST_SPIRIT_DEBUG_NODE( body );
    BOOST_SPIRIT_DEBUG_NODE( sequence );
    BOOST_SPIRIT_DEBUG_NODE( command );
    BOOST_SPIRIT_DEBUG_NODE( conditional );
    BOOST_SPIRIT_DEBUG_NODE( assignment );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_EXPRESSION_IPP__

// vim:ft=cpp et
