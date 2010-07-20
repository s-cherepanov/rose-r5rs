#ifndef __ROSE_GENERATOR_IMPL_DATUM_IPP__
#define __ROSE_GENERATOR_IMPL_DATUM_IPP__

#include "rose/generator/attributes.hpp"
#include "rose/generator/datum.hpp"

#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace rose {
namespace generator {

namespace phoenix = boost::phoenix;

template<
    typename Iterator,
    typename Delimiter
>
datum<Iterator, Delimiter>::datum() :
    datum::base_type(start)
{
    using karma::_1;
    using karma::_val;
    using karma::buffer;
    using karma::int_;
    using karma::lit;
    using phoenix::at_c;

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
        =   '('
            << (*datum_)                    [_1 = at_c<0>(_val)]
            << (-('.' << datum_))           [_1 = at_c<1>(_val)]
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
