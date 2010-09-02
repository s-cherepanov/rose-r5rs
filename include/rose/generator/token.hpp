#ifndef __ROSE_GENERATOR_TOKEN_HPP__
#define __ROSE_GENERATOR_TOKEN_HPP__

#include "rose/ast.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

using karma::grammar;
using karma::rule;
using karma::symbols;

template<typename Iterator>
struct boolean : grammar<Iterator, bool()> {
    boolean();

    rule<Iterator, bool()> start;
    symbols<bool, char const*> boolean_sym;

};  //  struct boolean

template<typename Iterator>
struct number : grammar<Iterator, int()> {
    number();

    rule<Iterator, int()> start;

};  //  struct boolean

template<typename Iterator>
struct character : grammar<Iterator, char()> {
    character();

    rule<Iterator, char()> character_;
    rule<Iterator, char()> character_name;

};  //  struct character

template<typename Iterator>
struct string : grammar<Iterator, ast_string()> {
    string();

    rule<Iterator, ast_string()> string_;
    rule<Iterator, char()>       string_element;

};  //  struct string

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_TOKEN_HPP__
