#ifndef __ROSE_NUMBER_HPP__
#define __ROSE_NUMBER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>

#include <complex>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct number :
    qi::grammar<Iterator, int()>
{
    number();

    qi::rule<Iterator, int()> start;
    
};  //  struct number

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_NUMBER_HPP__
