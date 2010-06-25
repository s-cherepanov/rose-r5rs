#ifndef __ROSE_PARSER_STRING_HPP__
#define __ROSE_PARSER_STRING_HPP__

#include "rose/ast/datum.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct string : qi::grammar<Iterator, ast::string()> {
    string();

    qi::rule<Iterator, ast::string()> start;
    qi::rule<Iterator, char()>        string_element;

};  //  struct string

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_STRING_HPP__
