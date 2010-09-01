#ifndef __ROSE_PARSER_CHARACTER_HPP__
#define __ROSE_PARSER_CHARACTER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator>
struct character : grammar<Iterator, char()> {
    character();

    rule<Iterator, char()> start;
    rule<Iterator, char()> character_name;

};

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_CHARACTER_HPP__
