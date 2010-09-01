#ifndef __ROSE_PARSER_PROCEDURE_CALL_HPP__
#define __ROSE_PARSER_PROCEDURE_CALL_HPP__

#include "rose/ast.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

using qi::grammar;
using qi::rule;

template<typename Iterator, typename Skipper>
struct expression;

template<typename Iterator, typename Skipper>
struct procedure_call : grammar<Iterator, ast_procedure_call(), Skipper> {
    typedef
        rose::parser::expression<Iterator, Skipper>
        expression_type;

    procedure_call(expression_type const*);

private:
    expression_type const*                 expression_ptr;
    rose::parser::token<Iterator, Skipper> token;

    rule<Iterator, ast_procedure_call(), Skipper> start;
    rule<Iterator, ast_procedure_call(), Skipper> procedure_call_;
    rule<Iterator, ast_expression(),     Skipper> operator_;
    rule<Iterator, ast_expression(),     Skipper> operand;

};  //  struct procedure_call

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_PARSER_PROCEDURE_CALL_HPP__
