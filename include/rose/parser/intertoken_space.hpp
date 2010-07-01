#ifndef __ROSE_INTERTOKEN_SPACE_HPP__
#define __ROSE_INTERTOKEN_SPACE_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator>
struct intertoken_space :
    qi::grammar<Iterator>
{
    intertoken_space();

    qi::rule<Iterator> start;
    qi::rule<Iterator> atmosphere;
    qi::rule<Iterator> whitespace;
    qi::rule<Iterator> comment;

};  //  struct intertoken_space

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_INTERTOKEN_SPACE_HPP__
