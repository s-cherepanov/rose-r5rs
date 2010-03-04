#ifndef __ROSE_IMPL_R5RS_GRAMMAR_HPP__
#define __ROSE_IMPL_R5RS_GRAMMAR_HPP__

#include "rose/r5rs_grammar.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

struct print_token {
    template<typename Type>
    void operator()(
            Type const& token,
            qi::unused_type,
            qi::unused_type ) const
    {
        std::cout << "{" << token << "}" << std::endl;
    }
    
};  //  struct print_token

template<
    typename Iterator,
    typename Skipper
>
r5rs_grammar<Iterator, Skipper>::r5rs_grammar() :
    r5rs_grammar::base_type( program )
{
    using spirit::_1;
    using spirit::lexeme;
    using spirit::raw;
    using qi::char_;

    program
        =  *( token[ print_token() ] )
        ;

    token
        =   raw
            [   lexeme[ boolean ]
            |   lexeme[ number ]
            |   lexeme[ identifier ]
            |   lexeme[ character ]
            |   lexeme[ string ]
            |   char_( "()'`,." )
            |   "#("
            |   ",@"
            ]
        ;

    program.name( "program" );

    BOOST_SPIRIT_DEBUG_NODE( program );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_R5RS_GRAMMAR_HPP__

// vim:ft=cpp
