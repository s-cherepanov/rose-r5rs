#ifndef __ROSE_DATUM_HPP__
#define __ROSE_DATUM_HPP__

#include "rose/ast/datum.hpp"
#include "rose/parser/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_rule.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct datum :
    qi::grammar<Iterator, ast::datum(), Skipper>
{
    datum();

    parser::token<Iterator, Skipper> token;

    qi::rule<Iterator, ast::datum(),  Skipper> datum_;
    qi::rule<Iterator, ast::datum(),  Skipper> simple_datum;
    qi::rule<Iterator, ast::symbol(), Skipper> symbol;
    qi::rule<Iterator, ast::datum(),  Skipper> compound_datum;
    qi::rule<Iterator, ast::list(),   Skipper> list;
    qi::rule<Iterator, ast::datum(),  Skipper> abbreviation;
    qi::rule<Iterator,                Skipper> abbrev_prefix;
    qi::rule<Iterator, ast::vector(), Skipper> vector;

};  //  struct datum

}   //  namespace parser
}   //  namespace rose

#endif  //  __ROSE_DATUM_HPP__
