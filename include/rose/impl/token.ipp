#ifndef __ROSE_IMPL_TOKEN_IPP__
#define __ROSE_IMPL_TOKEN_IPP__

#include "rose/token.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator>
boolean<Iterator>::boolean() :
    boolean::base_type( start )
{
    using qi::attr;

    start
        =   "#t" >> attr( true )
        |   "#f" >> attr( false )
        ;

    start.name( "boolean" );

    BOOST_SPIRIT_DEBUG_NODE( start );
}

template<typename Iterator>
string<Iterator>::string() :
    string::base_type( start )
{
    using ascii::graph;
    using ascii::space;
    using qi::attr;

    start
        =   '"' >> *( string_element - '"' ) >> '"'
        ;

    string_element
        =   ( ( graph | space ) - '"' - '\\' )
        |   ( "\\\"" >> attr( '"' ) )
        |   ( "\\\\" >> attr( '\\' ) )
        |   ( "\\n"  >> attr( '\n' ) )
        |   ( "\\t"  >> attr( '\t' ) )
        ;
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_TOKEN_IPP__
