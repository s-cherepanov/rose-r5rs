#ifndef __ROSE_GENERATOR_PROGRAM_HPP__
#define __ROSE_GENERATOR_PROGRAM_HPP__

#include "rose/ast/program.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;
namespace ast = rose::ast;

using karma::rule;

template<
    typename OutputIterator,
    typename Delimiter
>
struct program :
    karma::grammar<OutputIterator, ast::program(), Delimiter>
{
    program();

    rule<OutputIterator, ast::definition(), Delimiter> definition;
    rule<OutputIterator, ast::expression(), Delimiter> expression;

    rule<OutputIterator, ast::program(),    Delimiter> start;
    rule<OutputIterator, ast::expression(), Delimiter> command;
    rule<OutputIterator, ast::variable(),   Delimiter> variable;

};  //  struct program

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_PROGRAM_HPP__
