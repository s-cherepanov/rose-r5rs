#ifndef __ROSE_PARSER_IMPL_PROGRAM_HPP__
#define __ROSE_PARSER_IMPL_PROGRAM_HPP__

#include "rose/parser/program.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace repository = boost::spirit::repository;

template<typename Iterator, typename Skipper>
program<Iterator, Skipper>::program() :
    program::base_type(start),
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
        =   lexeme["#!" >> +(char_ - eol) >> eol]
        ;

    command
        =   expression
        ;
}

}   //  namespace rose

}   //  namespace parser

#endif  //  __ROSE_PARSER_IMPL_PROGRAM_HPP__

// vim:ft=cpp et
