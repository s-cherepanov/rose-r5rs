#ifndef __ROSE_PARSER_IMPL_DEFINITION_IPP__
#define __ROSE_PARSER_IMPL_DEFINITION_IPP__

#include "rose/parser/definition.hpp"

namespace rose {
namespace parser {

template<
    typename Iterator,
    typename Skipper
>
definition<Iterator, Skipper>::definition() :
    definition::base_type(start)
{
    start
        =   expression.definition
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_DEFINITION_IPP__

// vim:ft=cpp et
