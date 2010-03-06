#ifndef __ROSE_TOKEN_HPP__
#define __ROSE_TOKEN_HPP__

#include "rose/character.hpp"
#include "rose/identifier.hpp"
#include "rose/number.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

template<typename Iterator, typename Skipper>
struct token :
    qi::grammar<Iterator, Skipper>
{
    token();

    qi::rule<Iterator, Skipper> start;
    qi::rule<Iterator> delimiter;

    qi::rule<Iterator, std::string(), Skipper> identifier;
    qi::rule<Iterator, int(), Skipper>         number;
    qi::rule<Iterator, char(), Skipper>        character;
    qi::rule<Iterator, std::string(), Skipper> string;
    qi::rule<Iterator, bool(), Skipper>        boolean;

    qi::rule<Iterator, Skipper> lparen;
    qi::rule<Iterator, Skipper> rparen;
    qi::rule<Iterator, Skipper> sharp_lparen;
    qi::rule<Iterator, Skipper> single_quote;
    qi::rule<Iterator, Skipper> back_quote;
    qi::rule<Iterator, Skipper> comma;
    qi::rule<Iterator, Skipper> comma_at;
    qi::rule<Iterator, Skipper> dot;

private:
    rose::identifier<Iterator> identifier_;
    rose::number<Iterator>     number_;
    rose::character<Iterator>  character_;

    qi::rule<Iterator, bool()>        boolean_;
    qi::rule<Iterator, std::string()> string_;
    qi::rule<Iterator, char()>        string_element;

};  //  struct token

}   //  namespace rose

#endif  //  __ROSE_TOKEN_HPP__
