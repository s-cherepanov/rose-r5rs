#ifndef __ROSE_IMPL_DATUM_IPP__
#define __ROSE_IMPL_DATUM_IPP__

#include "rose/datum.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

template<
    typename Iterator,
    typename Skipper
>
datum<Iterator, Skipper>::datum() :
    datum::base_type( datum_ )
{
    using qi::char_;
    using qi::lexeme;

    datum_
        =   simple_datum
        |   compound_datum
        ;

    simple_datum
        =   lexeme[ boolean ]
        |   lexeme[ number ]
        |   lexeme[ character ]
        |   lexeme[ string ]
        |   symbol
        ;

    symbol
        =   lexeme[ identifier ]
        ;

    compound_datum
        =   list
        |   vector
        ;

    list
        =   '(' >> *datum_ >> ')'
        |   '(' >> +datum_ >> '.' >> datum_ >> ')'
        |   abbreviation
        ;

    abbreviation
        =   abbrev_prefix >> datum_
        ;

    //
    // NOTE:
    //
    // ",@" must comes first, or ',' as its prefix would be matched first.
    //
    abbrev_prefix
        =   ",@" | char_( "'`," )
        ;

    vector
        =   "#("  >> *datum_ >> ')'
        ;

    datum_          .name( "datum" );
    simple_datum    .name( "simple_datum" );
    symbol          .name( "symbol" );
    compound_datum  .name( "compound_datum" );
    list            .name( "list" );
    abbreviation    .name( "abbreviation" );
    abbrev_prefix   .name( "abbrev_prefix" );
    vector          .name( "vector" );

    BOOST_SPIRIT_DEBUG_NODE( datum_ );
    BOOST_SPIRIT_DEBUG_NODE( simple_datum );
    BOOST_SPIRIT_DEBUG_NODE( symbol );
    BOOST_SPIRIT_DEBUG_NODE( compound_datum );
    BOOST_SPIRIT_DEBUG_NODE( list );
    BOOST_SPIRIT_DEBUG_NODE( abbreviation );
    BOOST_SPIRIT_DEBUG_NODE( abbrev_prefix );
    BOOST_SPIRIT_DEBUG_NODE( vector );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_DATUM_IPP__
