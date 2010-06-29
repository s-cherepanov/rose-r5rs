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
    rose::generator::boolean<OutputIterator, Delimiter>   boolean;
    rose::generator::number<OutputIterator, Delimiter>    number;
    rose::generator::character<OutputIterator, Delimiter> character;
    rose::generator::string<OutputIterator, Delimiter>    string;

    rule<OutputIterator, ast::datum(),  Delimiter> start;
    rule<OutputIterator, ast::datum(),  Delimiter> datum_;
    rule<OutputIterator, ast::list(),   Delimiter> list;
    rule<OutputIterator, ast::vector(), Delimiter> vector;
    rule<OutputIterator, ast::symbol(), Delimiter> symbol;

};  //  struct datum

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_DATUM_HPP__
