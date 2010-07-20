#ifndef __ROSE_GENERATOR_PROGRAM_HPP__
#define __ROSE_GENERATOR_PROGRAM_HPP__

#include "rose/ast/program.hpp"
#include "rose/generator/expression.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

using karma::grammar;
using karma::rule;

template<
    typename Iterator,
    typename Delimiter
>
struct program :
    grammar<Iterator, ast_program(), Delimiter>
{
    program();

private:
    rose::generator::datum<Iterator, Delimiter> datum_;
    rose::generator::expression<Iterator, Delimiter> expression;

    rule<Iterator, ast_program(),    Delimiter> start;
    rule<Iterator, ast_expression(), Delimiter> command;
    rule<Iterator, ast_definition(), Delimiter> definition;

};  //  struct program

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_PROGRAM_HPP__
