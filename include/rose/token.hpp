#ifndef __ROSE_TOKEN_HPP__
#define __ROSE_TOKEN_HPP__

#include "rose/identifier.hpp"
#include "rose/character.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct boolean :
    qi::grammar<Iterator, bool()>
{
    boolean();

    qi::rule<Iterator, bool()> start;

};  //  struct boolean

template<typename Iterator>
struct string :
    qi::grammar<Iterator, std::string()>
{
    string();

    qi::rule<Iterator, std::string()> start;
    qi::rule<Iterator, char()> string_element;

};  //  struct string

}   //  namespace rose

#endif  //  __ROSE_TOKEN_HPP__
