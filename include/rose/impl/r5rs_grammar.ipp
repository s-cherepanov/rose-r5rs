#ifndef __ROSE_IMPL_R5RS_GRAMMAR_HPP__
#define __ROSE_IMPL_R5RS_GRAMMAR_HPP__

#include "rose/r5rs_grammar.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

template<
    typename Iterator,
    typename Skipper
>
r5rs_grammar<Iterator, Skipper>::r5rs_grammar() :
    r5rs_grammar::base_type( program )
{
    using spirit::lexeme;
    using spirit::raw;
    using qi::char_;

    program
        =  +command_or_definition
        ;

    command_or_definition
        =   command
        |   expression.definition
        ;

    command
        =   expression
        ;

    program              .name( "program" );
    command_or_definition.name( "command_or_definition" );
    command              .name( "command" );

    BOOST_SPIRIT_DEBUG_NODE( program );
    BOOST_SPIRIT_DEBUG_NODE( command_or_definition );
    BOOST_SPIRIT_DEBUG_NODE( command );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_R5RS_GRAMMAR_HPP__

// vim:ft=cpp
