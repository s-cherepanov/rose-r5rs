#ifndef __ROSE_GENERATOR_TOKEN_HPP__
#define __ROSE_GENERATOR_TOKEN_HPP__

#include "rose/ast/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;
namespace ast = rose::ast;

template<typename OutputIterator>
struct boolean :
    karma::grammar<OutputIterator, bool()>
{
    boolean();

    karma::rule<OutputIterator, bool()> start;
    karma::symbols<bool, char const*> boolean_sym;
    
};  //  struct boolean

template<typename OutputIterator>
struct character :
    karma::grammar<OutputIterator, char()>
{
    character();

    karma::rule<OutputIterator, char()> start;
    karma::rule<OutputIterator, char()> character_name;

};  //  struct character

template<typename OutputIterator>
struct string :
    karma::grammar<OutputIterator, ast::string()>
{
    string();

    karma::rule<OutputIterator, ast::string()> start;
    karma::rule<OutputIterator, char()>        string_element;
    
};  //  struct string

};  //  struct datum

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_TOKEN_HPP__
