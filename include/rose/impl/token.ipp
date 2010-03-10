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
    using qi::lit;
    using qi::no_case;

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
        =   no_case
            [
                "#t" >> attr( true )
            |   "#f" >> attr( false )
            ]
        ;

    string_
        =   '"' >> *( string_element - '"' ) >> '"'
        ;

    string_element
        =   ( ( graph | space ) - char_( "\"\\" ) )
        |   lit( "\\\"" ) >> attr( '"' )
        |   lit( "\\\\" ) >> attr( '\\' )
        |   lit( "\\n" )  >> attr( '\n' )
        |   lit( "\\t" )  >> attr( '\t' )
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

    identifier  .name( "identifier" );
    boolean     .name( "boolean" );
    number      .name( "number" );
    character   .name( "character" );
    string      .name( "string" );
    lparen      .name( "lparen" );
    rparen      .name( "rparen" );
    sharp_lparen.name( "sharp_lparen" );
    single_quote.name( "single_quote" );
    back_quote  .name( "back_quote" );
    comma       .name( "comma" );
    comma_at    .name( "comma_at" );
    dot         .name( "dot" );

    BOOST_SPIRIT_DEBUG_NODE( identifier );
    BOOST_SPIRIT_DEBUG_NODE( boolean );
    BOOST_SPIRIT_DEBUG_NODE( number );
    BOOST_SPIRIT_DEBUG_NODE( character );
    BOOST_SPIRIT_DEBUG_NODE( string );
    BOOST_SPIRIT_DEBUG_NODE( lparen );
    BOOST_SPIRIT_DEBUG_NODE( rparen );
    BOOST_SPIRIT_DEBUG_NODE( sharp_lparen );
}

}   //  namespace rose

#endif  //  __ROSE_IMPL_TOKEN_IPP__
