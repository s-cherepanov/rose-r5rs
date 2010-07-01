#ifndef __ROSE_GENERATOR_DATUM_HPP__
#define __ROSE_GENERATOR_DATUM_HPP__

#include "rose/ast/datum.hpp"
#include "rose/generator/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

namespace rose {
namespace generator {

namespace karma = boost::spirit::karma;

using karma::grammar;
using karma::rule;

template<
    typename OutputIterator,
    typename Delimiter
>
struct datum :
    grammar<OutputIterator, ast_datum(), Delimiter>
{
    datum();

private:
    rose::generator::boolean<OutputIterator, Delimiter>   boolean;
    rose::generator::number<OutputIterator, Delimiter>    number;
    rose::generator::character<OutputIterator, Delimiter> character;
    rose::generator::string<OutputIterator, Delimiter>    string;

    rule<OutputIterator, ast_datum(),  Delimiter> datum_;
    rule<OutputIterator, ast_datum(),  Delimiter> start;
    rule<OutputIterator, ast_list(),   Delimiter> list;
    rule<OutputIterator, ast_symbol(), Delimiter> symbol;
    rule<OutputIterator, ast_vector(), Delimiter> vector;

};  //  struct datum

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_DATUM_HPP__
