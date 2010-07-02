#ifndef __ROSE_GENERATOR_TOKEN_HPP__
#define __ROSE_GENERATOR_TOKEN_HPP__

#include "rose/ast/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

using karma::grammar;
using karma::rule;
using karma::symbols;

template<
    typename Iterator,
    typename Delimiter
>
struct boolean :
    grammar<Iterator, bool(), Delimiter>
{
    boolean();

    rule<Iterator, bool(), Delimiter> start;
    symbols<bool, char const*> boolean_sym;

};  //  struct boolean

template<
    typename Iterator,
    typename Delimiter
>
struct number :
    grammar<Iterator, int(), Delimiter>
{
    number();

    rule<Iterator, int(), Delimiter> start;

};  //  struct boolean

template<
    typename Iterator,
    typename Delimiter
>
struct character :
    grammar<Iterator, char(), Delimiter>
{
    character();

    rule<Iterator, char(), Delimiter> start;
    rule<Iterator, char()> character_;
    rule<Iterator, char()> character_name;

};  //  struct character

template<
    typename Iterator,
    typename Delimiter
>
struct string :
    grammar<Iterator, ast_string(), Delimiter>
{
    string();

    rule<Iterator, ast_string(), Delimiter> start;
    rule<Iterator, ast_string()> string_;
    rule<Iterator, char()>       string_element;

};  //  struct string

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_TOKEN_HPP__
