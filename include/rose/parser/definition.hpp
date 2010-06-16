#ifndef __ROSE_PARSER_DEFINITION_HPP__
#define __ROSE_PARSER_DEFINITION_HPP__

#include "rose/ast/expression.hpp"
#include "rose/parser/token.hpp"
#include "rose/parser/expression.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace ast = rose::ast;
namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct definition :
    qi::grammar<Iterator, ast::definition(), Skipper>
{
    definition();

private:
    parser::token<Iterator, Skipper> token;
    parser::expression<Iterator, Skipper> expression;

    qi::rule<Iterator, ast::definition(), Skipper> start;

};  //  struct definition

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_DEFINITION_HPP__
