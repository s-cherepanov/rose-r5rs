#ifndef __ROSE_TOKENIZER_HPP__
#define __ROSE_TOKENIZER_HPP__

#include "rose/character.hpp"
#include "rose/identifier.hpp"
#include "rose/number.hpp"
#include "rose/token.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

namespace rose {

namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
namespace spirit = boost::spirit;

template<
    typename Iterator,
    typename Skipper
>
struct tokenizer :
    qi::grammar<Iterator, Skipper>
{
    template<typename OutputIterator>
    tokenizer( OutputIterator& out ) :
        tokenizer::base_type( start )
    {
        using phoenix::ref;
        using qi::char_;
        using spirit::_1;
        using spirit::lexeme;
        using spirit::raw;

        start
            =  *token[ *( ref( out ) ) = _1 ]
            ;

        token
            =   raw
                [   lexeme[ boolean ]
                |   lexeme[ number ]
                |   lexeme[ identifier ]
                |   lexeme[ character ]
                |   lexeme[ string ]
                |   "#("
                |   ",@"
                |   char_( "()'`,." )
                ]
            ;

        start.name( "tokens" );
        token.name( "token" );

        BOOST_SPIRIT_DEBUG_NODE( start );
        BOOST_SPIRIT_DEBUG_NODE( token );
    }

    rose::identifier<Iterator>  identifier;
    rose::boolean<Iterator>     boolean;
    rose::number<Iterator>      number;
    rose::character<Iterator>   character;
    rose::string<Iterator>      string;

    qi::rule<Iterator, Skipper>                start;
    qi::rule<Iterator, std::string(), Skipper> token;

};  //  struct tokenizer

}   //  namespace rose

#endif  //  __ROSE_TOKENIZER_HPP__
