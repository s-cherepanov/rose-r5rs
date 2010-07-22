#ifndef __ROSE_GENERATOR_IMPL_TOKEN_IPP__
#define __ROSE_GENERATOR_IMPL_TOKEN_IPP__

#include "rose/generator/token.hpp"

namespace rose {
namespace generator {

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;

template<
    typename Iterator,
    typename Delimiter
>
boolean<Iterator, Delimiter>::boolean() :
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

template<
    typename Iterator,
    typename Delimiter
>
number<Iterator, Delimiter>::number() :
    number::base_type(start)
{
    using karma::int_;

    start
        =   int_
        ;
}

template<
    typename Iterator,
    typename Delimiter
>
character<Iterator, Delimiter>::character() :
    character::base_type(start)
{
    using karma::char_;
    using karma::graph;
    using karma::verbatim;

    start
        =   verbatim[character_]
        ;

    character_
        =   "#\\" << (character_name | graph)
        ;

    character_name
        =   &char_(' ')  << "space"
        |   &char_('\n') << "newline"
        |   &char_('\t') << "tab"
        ;
}

template<
    typename Iterator,
    typename Delimiter
>
string<Iterator, Delimiter>::string() :
    string::base_type(start)
{
    using ascii::space;
    using karma::char_;
    using karma::graph;
    using karma::verbatim;

    start
        =   verbatim[string_]
        ;

    string_
        =   '"' << *string_element << '"'
        ;

    string_element
        =   &char_('"')  << "\\\""
        |   &char_('\\') << "\\\\"
        |   graph
        |   space
        ;
}

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_IMPL_TOKEN_IPP__

// vim:ft=cpp et
