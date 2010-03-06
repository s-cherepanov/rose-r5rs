#ifndef __ROSE_R5RS_GRAMMAR_HPP__
#define __ROSE_R5RS_GRAMMAR_HPP__

#include "rose/datum.hpp"
#include "rose/expression.hpp"

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

    rose::expression<Iterator, Skipper> expression;

    qi::rule<Iterator, Skipper> program;
    qi::rule<Iterator, Skipper> command_or_definition;
    qi::rule<Iterator, Skipper> command;

};  //  struct r5rs_grammar

}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
