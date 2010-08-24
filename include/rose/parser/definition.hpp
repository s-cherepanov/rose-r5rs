#ifndef __ROSE_PARSER_DEFINITION_HPP__
#define __ROSE_PARSER_DEFINITION_HPP__

#include "rose/ast/program.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator, typename Skipper>
struct expression;

template<typename Iterator, typename Skipper>
struct definition : grammar<Iterator, ast_definition(), Skipper> {
    typedef
        rose::parser::expression<Iterator, Skipper>
        expression_type;

    definition(expression_type const*);

private:
    expression_type const* expression_ptr;
    rose::parser::token<Iterator, Skipper> token;

    rule<Iterator, ast_definition(), Skipper> start;
    rule<Iterator, ast_definition(), Skipper> plain_definition;
    rule<Iterator, ast_formals(),    Skipper> formals;
    rule<Iterator, ast_body(),       Skipper> body;
    rule<Iterator, ast_sequence(),   Skipper> sequence;

    rule<
        Iterator,
        ast_definition(),
        qi::locals<ast_formals, ast_body>,
        Skipper
    >
    procedure_definition;

};  //  struct definition

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_DEFINITION_HPP__
