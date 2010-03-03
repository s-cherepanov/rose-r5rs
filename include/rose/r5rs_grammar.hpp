#ifndef __ROSE_R5RS_GRAMMAR_HPP__
#define __ROSE_R5RS_GRAMMAR_HPP__

#include "rose/identifier.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct r5rs_grammar :
    qi::grammar<Iterator, Skipper>
{
    r5rs_grammar();

    identifier<Iterator> identifier_;
    qi::rule<Iterator, Skipper> program;
    qi::rule<Iterator, Skipper> identifier;

};  //  struct r5rs_grammar

}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
