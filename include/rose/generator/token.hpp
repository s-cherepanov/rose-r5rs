#ifndef __ROSE_GENERATOR_TOKEN_HPP__
#define __ROSE_GENERATOR_TOKEN_HPP__

#include "rose/ast/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;
namespace ast = rose::ast;

template<
    typename OutputIterator,
    typename Delimiter
>
struct boolean :
    karma::grammar<OutputIterator, bool(), Delimiter>
{
    boolean();

    karma::rule<OutputIterator, bool(), Delimiter> start;
    karma::symbols<bool, char const*> boolean_sym;

};  //  struct boolean

template<
    typename OutputIterator,
    typename Delimiter
>
struct number :
    karma::grammar<OutputIterator, int(), Delimiter>
{
    number();

    karma::rule<OutputIterator, int(), Delimiter> start;

};  //  struct boolean

template<
    typename OutputIterator,
    typename Delimiter
>
struct character :
    karma::grammar<OutputIterator, char(), Delimiter>
{
    character();

    karma::rule<OutputIterator, char(), Delimiter> start;
    karma::rule<OutputIterator, char()> character_;
    karma::rule<OutputIterator, char()> character_name;

};  //  struct character

template<
    typename OutputIterator,
    typename Delimiter
>
struct string :
    karma::grammar<OutputIterator, ast::string(), Delimiter>
{
    string();

    karma::rule<OutputIterator, ast::string(), Delimiter> start;
    karma::rule<OutputIterator, ast::string()> string_;
    karma::rule<OutputIterator, char()> string_element;

};  //  struct string

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_TOKEN_HPP__
