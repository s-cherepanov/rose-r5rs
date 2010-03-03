#ifndef __ROSE_IMPL_IDENTIFIER_IPP__
#define __ROSE_IMPL_IDENTIFIER_IPP__

#include "rose/identifier.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator>
identifier<Iterator>::identifier() :
    identifier::base_type( start )
{
    using ascii::alpha;
    using ascii::digit;
    using qi::char_;
    using qi::raw;

    start
        %=  initial >> *subsequent
        |   peculiar_identifier
        ;

    initial
        =   alpha | special_initial
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

    qi::debug( start );
    qi::debug( initial );
    qi::debug( peculiar_identifier );
    qi::debug( special_initial );
    qi::debug( special_subsequent );
    qi::debug( subsequent );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_IDENTIFIER_IPP__

// vim:ft=cpp
