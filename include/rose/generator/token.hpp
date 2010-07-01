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
    typename OutputIterator,
    typename Delimiter
>
struct boolean :
    grammar<OutputIterator, bool(), Delimiter>
{
    boolean();

    rule<OutputIterator, bool(), Delimiter> start;
    symbols<bool, char const*> boolean_sym;

};  //  struct boolean

template<
    typename OutputIterator,
    typename Delimiter
>
struct number :
    grammar<OutputIterator, int(), Delimiter>
{
    number();

    rule<OutputIterator, int(), Delimiter> start;

};  //  struct boolean

template<
    typename OutputIterator,
    typename Delimiter
>
struct character :
    grammar<OutputIterator, char(), Delimiter>
{
    character();

    rule<OutputIterator, char(), Delimiter> start;
    rule<OutputIterator, char()> character_;
    rule<OutputIterator, char()> character_name;

};  //  struct character

template<
    typename OutputIterator,
    typename Delimiter
>
struct string :
    grammar<OutputIterator, ast_string(), Delimiter>
{
    string();

    rule<OutputIterator, ast_string(), Delimiter> start;
    rule<OutputIterator, ast_string()> string_;
    rule<OutputIterator, char()>       string_element;

};  //  struct string

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_TOKEN_HPP__
