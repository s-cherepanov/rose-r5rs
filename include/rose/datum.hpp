#ifndef __ROSE_DATUM_HPP__
#define __ROSE_DATUM_HPP__

#include "rose/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

template<
    typename Iterator,
    typename Skipper
>
struct datum :
    qi::grammar<Iterator, Skipper>
{
    datum();

    rose::token<Iterator, Skipper> token;

    qi::rule<Iterator, Skipper> datum_;
    qi::rule<Iterator, Skipper> simple_datum;
    qi::rule<Iterator, Skipper> symbol;
    qi::rule<Iterator, Skipper> compound_datum;
    qi::rule<Iterator, Skipper> list;
    qi::rule<Iterator, Skipper> abbreviation;
    qi::rule<Iterator, Skipper> abbrev_prefix;
    qi::rule<Iterator, Skipper> vector;

};  //  struct datum

}   //  namespace rose

#endif  //  __ROSE_DATUM_HPP__
