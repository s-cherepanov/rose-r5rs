#ifndef __ROSE_IMPL_R5RS_GRAMMAR_HPP__
#define __ROSE_IMPL_R5RS_GRAMMAR_HPP__

#include "rose/parser/r5rs_grammar.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {
namespace parser {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

template<
    typename Iterator,
    typename Skipper
>
r5rs_grammar<Iterator, Skipper>::r5rs_grammar() :
    r5rs_grammar::base_type(program)
{
    using spirit::lexeme;
    using spirit::raw;
    using qi::char_;

    program
        =   +(command | definition)
        ;

    definition
        =   expression.definition
        ;

    command
        =   expression
        ;

    program   .name("program");
    definition.name("definition");
    command   .name("command");
}

}   //  namespace rose

}   //  namespace parser
#endif  //  __ROSE_IMPL_R5RS_GRAMMAR_HPP__

// vim:ft=cpp et
