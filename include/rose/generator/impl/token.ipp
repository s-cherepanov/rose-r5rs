#ifndef __ROSE_GENERATOR_IMPL_TOKEN_IPP__
#define __ROSE_GENERATOR_IMPL_TOKEN_IPP__

#include "rose/generator/token.hpp"

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;

template<typename OutputIterator>
boolean<OutputIterator>::boolean() :
    boolean::base_type(start)
{
    start
        =   boolean_sym
        ;

    boolean_sym.add
        (true,  "#t")
        (false, "#f")
        ;
}

template<typename OutputIterator>
character<OutputIterator>::character() :
    character::base_type(start)
{
    using karma::char_;
    using karma::graph;

    start
        =   "#\\" << (character_name | graph)
        ;

    character_name
        =   &char_(' ')  << "space"
        |   &char_('\n') << "newline"
        |   &char_('\t') << "tab"
        ;
}

template<typename OutputIterator>
string<OutputIterator>::string() :
    string::base_type(start)
{
    using ascii::space;
    using karma::char_;
    using karma::graph;

    start
        =   '"' << *string_element << '"'
        ;

    string_element
        =   graph
        |   space
        |   &char_('"')  << "\\\""
        |   &char_('\\') << "\\\\"
        |   &char_('\n') << "\\n"
        |   &char_('\t') << "\\t"
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_TOKEN_IPP__

// vim:ft=cpp et
