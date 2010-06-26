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
    using karma::string;
    using karma::verbatim;

    start
        =   boolean_
        |   int_
        |   character_
        |   string_
        |   symbol
        |   list
        |   vector
        ;

    symbol
        =   karma::attr_cast(string)
        ;

    list
        =   lit('(')
            << *start
            << -('.' << start)
            << ')'
        ;

    vector
        =   lit("#(")
            << *start
            << ')'
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_DATUM_IPP__

// vim:ft=cpp et
