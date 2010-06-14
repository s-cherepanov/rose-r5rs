#ifndef __ROSE_PARSER_IMPL_CHARACTER_IPP__
#define __ROSE_PARSER_IMPL_CHARACTER_IPP__

#include "rose/parser/character.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator>
character<Iterator>::character() :
    character::base_type(start)
{
    using ascii::graph;
    using qi::attr;
    using qi::no_case;

    //
    // NOTE:
    // 
    // `character_name' must comes before `graph', otherwise `#\newline' and
    // `#\space' would never be matched since their prefix `#\n' and `#\s' are
    // matched first.
    //
    start
        =   "#\\" >> (character_name | graph)
        ;

    character_name
        =   no_case
            [
                "space"   >> attr(' ')
            |   "newline" >> attr('\n')
            |   "tab"     >> attr('\t')
            ]
        ;

    start         .name("character");
    character_name.name("character_name");
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_IMPL_CHARACTER_IPP__

// vim:ft=cpp et
