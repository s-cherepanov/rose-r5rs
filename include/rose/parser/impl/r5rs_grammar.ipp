#ifndef __ROSE_IMPL_R5RS_GRAMMAR_HPP__
#define __ROSE_IMPL_R5RS_GRAMMAR_HPP__

#include "rose/parser/r5rs_grammar.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace repository = boost::spirit::repository;

template<
    typename Iterator,
    typename Skipper
>
r5rs_grammar<Iterator, Skipper>::r5rs_grammar() :
    r5rs_grammar::base_type(start),
    definition(&expression)
{
    using qi::char_;
    using qi::eol;
    using qi::lexeme;
    using qi::omit;
    using repository::qi::confix;

    start
        =   -omit[shebang]
            >> +(command | definition)
        ;

    shebang
        =   lexeme[confix("#!", eol)[char_]]
        ;

    command
        =   expression
        ;
}

}   //  namespace rose

}   //  namespace parser

#endif  //  __ROSE_IMPL_R5RS_GRAMMAR_HPP__

// vim:ft=cpp et
