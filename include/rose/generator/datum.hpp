#ifndef __ROSE_GENERATOR_DATUM_HPP__
#define __ROSE_GENERATOR_DATUM_HPP__

#include "rose/ast/datum.hpp"
#include "rose/generator/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace ast = rose::ast;
namespace karma = boost::spirit::karma;

using karma::rule;

template<
    typename OutputIterator,
    typename Delimiter
>
struct datum :
    karma::grammar<OutputIterator, ast::datum(), Delimiter>
{
    datum();

private:
    generator::boolean<OutputIterator>   boolean_;
    generator::character<OutputIterator> character_;
    generator::string<OutputIterator>    string_;

    rule<OutputIterator, ast::datum(),      Delimiter> start;
    rule<OutputIterator, ast::list(),       Delimiter> list;
    rule<OutputIterator, ast::vector(),     Delimiter> vector;
    rule<OutputIterator, ast::symbol(),     Delimiter> symbol;
    rule<OutputIterator, ast::variable(),   Delimiter> variable;
    rule<OutputIterator, ast::identifier(), Delimiter> identifier;

};  //  struct datum

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_DATUM_HPP__
