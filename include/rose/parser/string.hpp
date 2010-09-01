#ifndef __ROSE_PARSER_STRING_HPP__
#define __ROSE_PARSER_STRING_HPP__

#include "rose/ast/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator>
struct string : grammar<Iterator, ast_string()> {
    string();

    rule<Iterator, ast_string()> start;
    rule<Iterator, char()>        string_element;

};  //  struct string

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_STRING_HPP__
