#ifndef __ROSE_IMPL_NUMBER_IPP__
#define __ROSE_IMPL_NUMBER_IPP__

#include "rose/number.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator>
number<Iterator>::number() :
    number::base_type( start )
{
    using qi::int_;

    start
        =   int_;
        ;
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_NUMBER_IPP__
