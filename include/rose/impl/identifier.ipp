#ifndef __ROSE_IMPL_IDENTIFIER_IPP__
#define __ROSE_IMPL_IDENTIFIER_IPP__

#include "rose/identifier.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

template<typename Iterator>
identifier<Iterator>::identifier() :
    identifier::base_type( start )
{
    using ascii::alpha;
    using ascii::digit;
    using qi::char_;
    using qi::no_case;
    using qi::raw;

    start
        =   raw
            [
                initial >> *subsequent
            |   peculiar_identifier
            ]
        ;

    initial
        =   no_case[ alpha ] | special_initial
        ;

    special_initial
        =   char_( "!$%&*/:<=>?^_~" )
        ;

    subsequent
        =   initial | digit | special_subsequent
        ;

    special_subsequent
        =   char_( "+-.@" )
        ;

    peculiar_identifier
        =   char_( "+-" ) | "..."
        ;

    start               .name( "identifier" );
    initial             .name( "initial" );
    peculiar_identifier .name( "peculiar_identifier" );
    special_initial     .name( "special_initial" );
    special_subsequent  .name( "special_subsequent" );
    subsequent          .name( "subsequent" );

    BOOST_SPIRIT_DEBUG_NODE( start );
    BOOST_SPIRIT_DEBUG_NODE( initial );
    BOOST_SPIRIT_DEBUG_NODE( peculiar_identifier );
    BOOST_SPIRIT_DEBUG_NODE( special_initial );
    BOOST_SPIRIT_DEBUG_NODE( special_subsequent );
    BOOST_SPIRIT_DEBUG_NODE( subsequent );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_IDENTIFIER_IPP__

// vim:ft=cpp
