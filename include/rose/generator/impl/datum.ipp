#ifndef __ROSE_GENERATOR_IMPL_DATUM_IPP__
#define __ROSE_GENERATOR_IMPL_DATUM_IPP__

#include "rose/generator/attributes.hpp"
#include "rose/generator/datum.hpp"

namespace rose {
namespace generator {

template<
    typename OutputIterator,
    typename Delimiter
>
datum<OutputIterator, Delimiter>::datum() :
    datum::base_type(start)
{
    using karma::int_;
    using karma::lit;

    start
        =   datum_.alias()
        ;

    datum_
        =   boolean
        |   number
        |   character
        |   string
        |   symbol
        |   list
        |   vector
        ;

    symbol
        =   karma::attr_cast(karma::string)
        ;

    list
        =   lit('(')
            << *datum_
            << -('.' << datum_)
            << ')'
        ;

    vector
        =   lit("#(")
            << *datum_
            << ')'
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_DATUM_IPP__

// vim:ft=cpp et
