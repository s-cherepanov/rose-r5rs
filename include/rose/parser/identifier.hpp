#ifndef __ROSE_IDENTIFIER_HPP__
#define __ROSE_IDENTIFIER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

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

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_IDENTIFIER_HPP__
