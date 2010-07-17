#ifndef __ROSE_IMPL_DATUM_IPP__
#define __ROSE_IMPL_DATUM_IPP__

#include "rose/parser/datum.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
datum<Iterator, Skipper>::datum() :
    datum::base_type(start)
{
    using phoenix::at_c;
    using phoenix::push_back;
    using qi::_1;
    using qi::_val;

    start
        =   datum_.alias()
        ;

    datum_
       %=   token.boolean
        |   token.number
        |   token.character
        |   token.string
        |   symbol
        |   list
        |   vector
        ;

    symbol
        =   token.identifier.alias()
        ;

    list
        =   token.lparen >> token.rparen
        |   token.lparen
            >> +datum_                      [push_back(at_c<0>(_val), _1)]
            >> -(token.dot >> (datum_       [at_c<1>(_val) = _1]))
            >> token.rparen
        ;

    abbreviation
        =   abbrev_prefix >> datum_
        ;

    // NOTE: `comma_at' must comes before `comma'
    abbrev_prefix
        =   token.single_quote
        |   token.back_quote
        |   token.comma_at
        |   token.comma
        ;

    vector
        =   token.sharp_lparen
            >> token.rparen
        |   token.sharp_lparen
            >> +datum_                      [push_back(_val, _1)]
            >> token.rparen
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_DATUM_IPP__

// vim:ft=cpp et
