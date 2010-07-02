#ifndef __ROSE_DATUM_HPP__
#define __ROSE_DATUM_HPP__

#include "rose/ast/datum.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct datum :
    qi::grammar<Iterator, ast_datum(), Skipper>
{
    datum();

	rose::parser::token<Iterator, Skipper> token;

    qi::rule<Iterator, ast_datum(),  Skipper> abbreviation;
    qi::rule<Iterator, ast_datum(),  Skipper> compound_datum;
    qi::rule<Iterator, ast_datum(),  Skipper> datum_;
    qi::rule<Iterator, ast_datum(),  Skipper> simple_datum;
    qi::rule<Iterator, ast_datum(),  Skipper> start;
    qi::rule<Iterator, ast_list(),   Skipper> list;
    qi::rule<Iterator, ast_symbol(), Skipper> symbol;
    qi::rule<Iterator, ast_vector(), Skipper> vector;
    qi::rule<Iterator,               Skipper> abbrev_prefix;

};  //  struct datum

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_DATUM_HPP__
