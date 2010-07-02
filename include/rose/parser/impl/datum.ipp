#ifndef __ROSE_IMPL_DATUM_IPP__
#define __ROSE_IMPL_DATUM_IPP__

#include "rose/parser/datum.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace parser {

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

template<
    typename Iterator,
    typename Skipper
>
datum<Iterator, Skipper>::datum() :
    datum::base_type(start)
{
    using qi::char_;
    using qi::lexeme;
    using namespace qi::labels;

    using phoenix::at_c;
    using phoenix::push_back;

    start
        =   datum_.alias()
        ;

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

    abbreviation  .name("abbreviation");
    compound_datum.name("compound_datum");
    datum_        .name("datum");
    simple_datum  .name("simple_datum");
    start         .name("start");
    list          .name("list");
    symbol        .name("symbol");
    vector        .name("vector");
    abbrev_prefix .name("list");
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_DATUM_IPP__

// vim:ft=cpp et
