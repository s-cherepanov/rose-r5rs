#ifndef __ROSE_R5RS_GRAMMAR_HPP__
#define __ROSE_R5RS_GRAMMAR_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/definition.hpp"
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
    qi::grammar<Iterator, ast::program(), Skipper>
{
    r5rs_grammar();

private:
    parser::definition<Iterator, Skipper> definition;
    parser::expression<Iterator, Skipper> expression;

    qi::rule<Iterator, ast::program(),    Skipper> start;
    qi::rule<Iterator, ast::expression(), Skipper> command;

};  //  struct r5rs_grammar

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
