#ifndef __ROSE_PARSER_IMPL_BOOLEAN_IPP__
#define __ROSE_PARSER_IMPL_BOOLEAN_IPP__

#include "rose/parser/boolean.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<typename Iterator>
boolean<Iterator>::boolean() :
    boolean::base_type(start)
{
    using qi::attr;
    using qi::no_case;

    start
        =   no_case
            [
                "#t" >> attr(true)
            |   "#f" >> attr(false)
            ]
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_BOOLEAN_IPP__

// vim:ft=cpp et
