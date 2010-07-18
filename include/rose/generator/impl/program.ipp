#ifndef __ROSE_GENERATOR_IMPL_PROGRAM_IPP__
#define __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

#include "rose/generator/program.hpp"

namespace rose {
namespace generator {

template<
    typename Iterator,
    typename Delimiter
>
program<Iterator, Delimiter>::program() :
    program::base_type(start)
{
    start
        =   +(command | definition)
        ;

    command
        =   expression
        ;

    definition
        =   expression.definition
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

// vim:ft=cpp et
