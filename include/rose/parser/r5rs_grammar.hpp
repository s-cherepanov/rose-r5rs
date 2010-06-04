#ifndef __ROSE_R5RS_GRAMMAR_HPP__
#define __ROSE_R5RS_GRAMMAR_HPP__

#include "rose/parser/datum.hpp"
#include "rose/parser/expression.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct r5rs_grammar :
    qi::grammar<Iterator, Skipper>
{
    r5rs_grammar();

    parser::expression<Iterator, Skipper> expression;

    qi::rule<Iterator, Skipper> program;
    qi::rule<Iterator, Skipper> command_or_definition;
    qi::rule<Iterator, Skipper> command;

};  //  struct r5rs_grammar

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
