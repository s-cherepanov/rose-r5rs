#ifndef __ROSE_IMPL_DATUM_IPP__
#define __ROSE_IMPL_DATUM_IPP__

#include "rose/datum.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;

template<
    typename Iterator,
    typename Skipper
>
datum<Iterator, Skipper>::datum() :
    datum::base_type(datum_)
{
    using qi::char_;
    using qi::lexeme;
    using namespace qi::labels;

    using phoenix::at_c;
    using phoenix::push_back;

    datum_
        =   simple_datum
        |   compound_datum
        ;

    simple_datum
       %=   token.boolean
        |   token.number
        |   token.character
        |   token.string
        |   symbol
        ;

    symbol
        =   token.identifier.alias()
        ;

    compound_datum
       %=   list
        |   vector
        ;

    list
        =   token.lparen
            >> *datum_                      [push_back(at_c<0>(_val), _1)]
            >> token.rparen
        |   token.lparen
            >> +datum_                      [push_back(at_c<0>(_val), _1)]
            >> token.dot
            >> datum_                       [at_c<1>(_val) = _1]
            >> token.rparen
        |   abbreviation
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
            >> *datum_                      [push_back(_val, _1)]
            >> token.rparen
        ;

    datum_        .name("datum");
    simple_datum  .name("simple_datum");
    symbol        .name("symbol");
    compound_datum.name("compound_datum");
    list          .name("list");
    abbreviation  .name("abbreviation");
    abbrev_prefix .name("abbrev_prefix");
    vector        .name("vector");
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_DATUM_IPP__

// vim:ft=cpp
