#ifndef __ROSE_IDENTIFIER_HPP__
#define __ROSE_IDENTIFIER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

using qi::grammar;
using qi::rule;

template<typename Iterator>
struct identifier : qi::grammar<Iterator, std::string()> {
    identifier();

    rule<Iterator, std::string()> start;
    rule<Iterator> initial;
    rule<Iterator> peculiar_identifier;
    rule<Iterator> special_initial;
    rule<Iterator> special_subsequent;
    rule<Iterator> subsequent;

};  //  struct identifier

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IDENTIFIER_HPP__
