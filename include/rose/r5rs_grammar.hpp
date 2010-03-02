#ifndef __ROSE_R5RS_GRAMMAR_HPP__
#define __ROSE_R5RS_GRAMMAR_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;

template<typename Iterator, typename Lexer>
struct r5rs_grammar :
    qi::grammar<Iterator, qi::in_state_skipper<Lexer> >
{
    typedef Iterator iterator_type;

    typedef qi::in_state_skipper<Lexer> skipper_type;

    template<typename TokenDef>
    r5rs_grammar( TokenDef const& token ) :
        r5rs_grammar::base_type( program )
    {
        using qi::lit;

        program
            =   *token
            ;

    }

    qi::rule<iterator_type, skipper_type> program;

};  //  struct r5rs_grammar

}   //  namespace rose

#endif  //  __ROSE_R5RS_GRAMMAR_HPP__
