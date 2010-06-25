#ifndef __ROSE_IMPL_INTERTOKEN_SPACE_HPP__
#define __ROSE_IMPL_INTERTOKEN_SPACE_HPP__

#include "rose/parser/intertoken_space.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator>
intertoken_space<Iterator>::intertoken_space() :
    intertoken_space::base_type(start)
{
    using ascii::char_;
    using ascii::alpha;
    using qi::eol;

    start
        =   +atmosphere
        ;

    atmosphere
        =   whitespace | comment
        ;

    whitespace
        =   char_(" \n")
        ;

    comment
        =   ';' >> *(char_ - eol) >> eol
        ;
}

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IMPL_INTERTOKEN_SPACE_HPP__

// vim:ft=cpp et
