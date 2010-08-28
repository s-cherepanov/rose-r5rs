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

template<typename Iterator, typename Delimiter>
struct datum : grammar<Iterator, ast_datum(), Delimiter> {
    datum();

private:
    rose::generator::boolean<Iterator>   boolean;
    rose::generator::number<Iterator>    number;
    rose::generator::character<Iterator> character;
    rose::generator::string<Iterator>    string;

    rule<Iterator, ast_datum(),  Delimiter> datum_;
    rule<Iterator, ast_datum(),  Delimiter> start;
    rule<Iterator, ast_list(),   Delimiter> list;
    rule<Iterator, ast_symbol(), Delimiter> symbol;
    rule<Iterator, ast_vector(), Delimiter> vector;

};  //  struct datum

}   //  namespace generator
}   //  namespace rose

#endif  //  __ROSE_GENERATOR_DATUM_HPP__
