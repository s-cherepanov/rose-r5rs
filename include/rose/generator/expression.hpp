#ifndef __ROSE_GENERATOR_EXPRESSION_HPP__
#define __ROSE_GENERATOR_EXPRESSION_HPP__

#include "rose/ast/program.hpp"
#include "rose/generator/datum.hpp"
#include "rose/generator/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

using karma::grammar;
using karma::rule;

template<typename Iterator, typename Delimiter>
struct expression : grammar<Iterator, ast_expression(), Delimiter> {
    expression();

    rule<Iterator, ast_definition(), Delimiter> definition;

private:
    rose::generator::datum<Iterator, Delimiter> datum;
    rose::generator::boolean<Iterator>          boolean;
    rose::generator::number<Iterator>           number;
    rose::generator::character<Iterator>        character;
    rose::generator::string<Iterator>           string;

    rule<Iterator, ast_assignment(),        Delimiter> assignment;
    rule<Iterator, ast_body(),              Delimiter> body;
    rule<Iterator, ast_conditional(),       Delimiter> conditional;
    rule<Iterator, ast_expression(),        Delimiter> expression_;
    rule<Iterator, ast_expression(),        Delimiter> start;
    rule<Iterator, ast_formals(),           Delimiter> formals;
    rule<Iterator, ast_lambda_expression(), Delimiter> lambda_expression;
    rule<Iterator, ast_procedure_call(),    Delimiter> procedure_call;
    rule<Iterator, ast_quotation(),         Delimiter> quotation;
    rule<Iterator, ast_variable(),          Delimiter> variable;

};  //  struct expression

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_EXPRESSION_HPP__
