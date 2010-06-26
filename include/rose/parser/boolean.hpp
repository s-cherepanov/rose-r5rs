#ifndef __ROSE_PARSER_BOOLEAN_HPP__
#define __ROSE_PARSER_BOOLEAN_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct boolean : qi::grammar<Iterator, bool()> {
    boolean();

    qi::rule<Iterator, bool()> start;

};  //  struct boolean

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_BOOLEAN_HPP__
