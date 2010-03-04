#ifndef __ROSE_R5RS_GRAMMAR_HPP__
#define __ROSE_R5RS_GRAMMAR_HPP__

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
struct r5rs_grammar :
    qi::grammar<Iterator, Skipper>
{
    r5rs_grammar();

    rose::identifier<Iterator>  identifier;
    rose::boolean<Iterator>     boolean;
    rose::number<Iterator>      number;
    rose::character<Iterator>   character;
    rose::string<Iterator>      string;

    qi::rule<Iterator, Skipper>                program;
    qi::rule<Iterator, std::string(), Skipper> token;

};  //  struct r5rs_grammar

}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
