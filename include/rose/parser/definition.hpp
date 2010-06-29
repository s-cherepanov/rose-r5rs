#ifndef __ROSE_PARSER_DEFINITION_HPP__
#define __ROSE_PARSER_DEFINITION_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace ast = rose::ast;
namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct expression;

template<
    typename Iterator,
    typename Skipper
>
struct definition :
    qi::grammar<Iterator, ast::definition(), Skipper>
{
    typedef
        rose::parser::expression<Iterator, Skipper>
        expression_type;

    definition(expression_type const*);

private:
    expression_type const* expression_ptr;
	rose::parser::token<Iterator, Skipper> token;

    qi::rule<Iterator, ast::definition(), Skipper> start;

};  //  struct definition

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_DEFINITION_HPP__
