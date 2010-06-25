#ifndef __ROSE_GENERATOR_IMPL_PROGRAM_IPP__
#define __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

#include "rose/generator/program.hpp"

#include <boost/spirit/include/karma.hpp>

namespace boost {
namespace spirit {
namespace traits {

using rose::ast::expression;

#define ENABLE_ATTR_CAST(target, repr)\
    template<>\
    struct transform_attribute<target const, std::string> {\
        typedef std::string type;\
        static type pre(target const&) {\
            return repr;\
        }\
    };

ENABLE_ATTR_CAST(expression, "{E}")

#undef ENABLE_ATTR_CAST

}   //  namespace traits
}   //  namespace spirit
}   //  namespace boost

namespace rose {
namespace generator {

template<
    typename OutputIterator,
    typename Delimiter
>
program<OutputIterator, Delimiter>::program() :
    program::base_type(start)
{
    using karma::lit;
    using karma::string;

    start
        =   +(command | definition)
        ;

    command
        =   expression.alias()
        ;

    definition
        =   lit('(') << "define"
            << variable
            << expression
            << ')'
        ;

    expression
        =   karma::attr_cast(string)
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_PROGRAM_IPP__

// vim:ft=cpp et
