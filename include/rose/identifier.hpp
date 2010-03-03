#ifndef __ROSE_IDENTIFIER_HPP__
#define __ROSE_IDENTIFIER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator>
struct identifier :
    qi::grammar<Iterator, std::string()>
{
    identifier();

    qi::rule<Iterator, std::string()> start;
    qi::rule<Iterator> initial;
    qi::rule<Iterator> peculiar_identifier;
    qi::rule<Iterator> special_initial;
    qi::rule<Iterator> special_subsequent;
    qi::rule<Iterator> subsequent;

};  //  struct identifier

}   //  namespace rose

#endif  //  __ROSE_IDENTIFIER_HPP__
