#ifndef __ROSE_DATUM_HPP__
#define __ROSE_DATUM_HPP__

#include "rose/character.hpp"
#include "rose/identifier.hpp"
#include "rose/number.hpp"
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

    rose::identifier<Iterator>  identifier;
    rose::boolean<Iterator>     boolean;
    rose::number<Iterator>      number;
    rose::character<Iterator>   character;
    rose::string<Iterator>      string;

    qi::rule<Iterator, Skipper> start;
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
