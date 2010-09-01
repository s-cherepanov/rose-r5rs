#ifndef __ROSE_PARSER_PROGRAM_HPP__
#define __ROSE_PARSER_PROGRAM_HPP__

#include "rose/ast.hpp"
#include "rose/parser/definition.hpp"
#include "rose/parser/expression.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator, typename Skipper>
struct program : grammar<Iterator, ast_program(), Skipper> {
    program();

private:
    rose::parser::expression<Iterator, Skipper> expression;
    rose::parser::definition<Iterator, Skipper> definition;

    rule<Iterator, ast_program(),    Skipper> start;
    rule<Iterator, ast_expression(), Skipper> command;
    rule<Iterator,                   Skipper> shebang;

};  //  struct program

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_PROGRAM_HPP__
