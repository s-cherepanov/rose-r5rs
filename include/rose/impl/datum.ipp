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
    datum::base_type( start )
{
    using qi::char_;
    using qi::lexeme;

    start
        =   datum_.alias()
        ;

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
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_DATUM_IPP__
