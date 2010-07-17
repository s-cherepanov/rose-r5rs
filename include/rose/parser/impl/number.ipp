#ifndef __ROSE_IMPL_NUMBER_IPP__
#define __ROSE_IMPL_NUMBER_IPP__

#include "rose/parser/number.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

template<typename Iterator>
number<Iterator>::number() :
    number::base_type(start)
{
    using qi::int_;

    start
        =   int_;
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_NUMBER_IPP__

// vim:ft=cpp et
