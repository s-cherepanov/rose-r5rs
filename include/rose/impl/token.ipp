#ifndef __ROSE_IMPL_TOKEN_IPP__
#define __ROSE_IMPL_TOKEN_IPP__

#include "rose/token.hpp"

#include <boost/spirit/include/phoenix_operator.hpp>

namespace rose {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Iterator, typename Skipper>
token<Iterator, Skipper>::token() :
    token::base_type( start )
{
    using ascii::graph;
    using ascii::space;
    using qi::attr;
    using qi::char_;
    using qi::eoi;
    using qi::lexeme;

    start
        =   identifier
        |   boolean
        |   number
        |   character
        |   string
        |   lparen
        |   rparen
        |   sharp_lparen
        |   single_quote
        |   back_quote
        |   comma
        |   comma_at
        |   dot
        ;

    delimiter
        =   space | char_( "()\";" ) | eoi
        ;

    boolean_
        =   "#t" >> attr( true )
        |   "#f" >> attr( false )
        ;

    string_
        =   '"' >> *( string_element - '"' ) >> '"'
        ;

    string_element
        =   ( ( graph | space ) - '"' - '\\' )
        |   ( "\\\"" >> attr( '"' ) )
        |   ( "\\\\" >> attr( '\\' ) )
        |   ( "\\n"  >> attr( '\n' ) )
        |   ( "\\t"  >> attr( '\t' ) )
        ;

    identifier   = lexeme[ identifier_ >> &delimiter ];
    number       = lexeme[ number_     >> &delimiter ];
    character    = lexeme[ character_  >> &delimiter ];
    dot          = lexeme[ '.'         >> &delimiter ];
    boolean      = lexeme[ boolean_ ];
    string       = lexeme[ string_ ];
    lparen       = lexeme[ '('  ];
    rparen       = lexeme[ ')'  ];
    sharp_lparen = lexeme[ "#(" ];
    single_quote = lexeme[ '\'' ];
    back_quote   = lexeme[ '`' ];
    comma        = lexeme[ ',' ];
    comma_at     = lexeme[ ",@" ];
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_TOKEN_IPP__
