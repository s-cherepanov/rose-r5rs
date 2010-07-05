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

using namespace rose;
using qi::grammar;
using qi::rule;

template<
    typename Iterator,
    typename Skipper
>
struct r5rs_grammar :
    grammar<Iterator, ast_program(), Skipper>
{
    r5rs_grammar();

private:
    rose::parser::expression<Iterator, Skipper> expression;
    rose::parser::definition<Iterator, Skipper> definition;

    rule<Iterator, ast_program(),    Skipper> start;
    rule<Iterator, ast_expression(), Skipper> command;

};  //  struct r5rs_grammar

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
