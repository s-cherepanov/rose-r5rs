#ifndef __ROSE_R5RS_LEXER_HPP__
#define __ROSE_R5RS_LEXER_HPP__

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_algorithm.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>

namespace rose {

namespace lex = boost::spirit::lex;

template<typename Lexer>
struct r5rs_tokens : lex::lexer<Lexer> {
    r5rs_tokens() {
        this->self.add_pattern
            // Skipper
            ( "whitespace",          "[ \\n]" )
            ( "comment",             ";.*$" )
            ( "atmosphere",          "{whitespace}|{comment}" )

            // Identifier
            ( "special_initial",     "[!$%&*/:<=>?^_~]" )
            ( "initial",             "[a-z]|{special_initial}" )
            ( "special_subsequent",  "[+-.@]" )
            ( "subsequent",          "{initial}|\\d|{special_subsequent}" )
            ( "peculiar_identifier", "\\+|-|\\.\\.\\." )

            // Character
            ( "character_name",      "space|newline" )

            // Number
            ( "radix_16",            "#x" )
            ( "radix_10",            "#d" )
            ( "radix_8",             "#o" )
            ( "radix_2",             "#b" )
            ( "exactness",           "#[ie]" )
            ( "sign",                "[+\\-]" )
            ( "exponent_marker",     "[esfdl]" )
            ( "suffix",              "{exponent_marker}{sign}?[0-9]+" )

            ( "prefix_2",            "{radix_2}{exactness}"
                                     "|{exactness}{radix_2}"
                                     "|{radix_2}" )
            ( "uinteger_2",          "[01]+#*" )
            ( "ureal_2",             "{uinteger_2}"
                                     "|{uinteger_2}\\/{uinteger_2}" )
            ( "real_2",              "{sign}?{ureal_2}" )
            ( "complex_2",           "{real_2}"
                                     "|{real_2}@{real_2}"
                                     "|{real_2}{sign}{ureal_2}i"
                                     "|{real_2}{sign}i"
                                     "|{sign}{ureal_2}i"
                                     "|{sign}i" )
            ( "num_2",               "{prefix_2}{complex_2}" )

            ( "prefix_8",            "{radix_8}{exactness}"
                                     "|{exactness}{radix_8}"
                                     "|{radix_8}" )
            ( "uinteger_8",          "[0-7]+#*" )
            ( "ureal_8",             "{uinteger_8}"
                                     "|{uinteger_8}\\/{uinteger_8}" )
            ( "real_8",              "{sign}?{ureal_8}" )
            ( "complex_8",           "{real_8}"
                                     "|{real_8}@{real_8}"
                                     "|{real_8}{sign}{ureal_8}i"
                                     "|{real_8}{sign}i"
                                     "|{sign}{ureal_8}i"
                                     "|{sign}i" )
            ( "num_8",               "{prefix_8}{complex_8}" )

            ( "prefix_10",           "{radix_10}{exactness}"
                                     "|{exactness}{radix_10}"
                                     "|{radix_10}"
                                     "|{exactness}" )
            ( "uinteger_10",         "[0-9]+#*" )
            ( "decimal_10",          "{uinteger_10}{suffix}?"
                                     "|\\.[0-9]+#*{suffix}?"
                                     "|[0-9]+\\.[0-9]*#*{suffix}?"
                                     "|[0-9]+\\.[0-9]*#*{suffix}?"
                                     "|[0-9]+#+\\.#*{suffix}?" )
            ( "ureal_10",            "{uinteger_10}"
                                     "|{uinteger_10}\\/{uinteger_10}"
                                     "|{decimal_10}" )
            ( "real_10",             "{sign}?{ureal_10}" )
            ( "complex_10",          "{real_10}"
                                     "|{real_10}@{real_10}"
                                     "|{real_10}{sign}{ureal_10}i"
                                     "|{real_10}{sign}i"
                                     "|{sign}{ureal_10}i"
                                     "|{sign}i" )
            ( "num_10",              "{prefix_10}?{complex_10}" )

            ( "prefix_16",           "{radix_16}{exactness}"
                                     "|{exactness}{radix_16}"
                                     "|{radix_16}" )
            ( "uinteger_16",         "[0-9a-f]+#*" )
            ( "ureal_16",            "{uinteger_16}"
                                     "|{uinteger_16}\\/{uinteger_16}" )
            ( "real_16",             "{sign}?{ureal_16}" )
            ( "complex_16",          "{real_16}"
                                     "|{real_16}@{real_16}"
                                     "|{real_16}{sign}{ureal_16}i"
                                     "|{real_16}{sign}i"
                                     "|{sign}{ureal_16}i"
                                     "|{sign}i" )
            ( "num_16",              "{prefix_16}{complex_16}" )

            // String
            ( "string_element",      "[^\\\"]|\\\"|\\\\" )
            ;

        delimiter         = "{whitespace}|[()\";]";
        intertoken_space  = "{atmosphere}+";
        identifier        = "{initial}{subsequent}*|{peculiar_identifier}";
        boolean           = "#t|#f";
        character         = "#\\\\({character_name}|[\x20-\x7e])";
        string            = "\\\"{string_element}*\\\"";
        number            = "{num_2}|{num_8}|{num_10}|{num_16}";
        lparen            = "\\(";
        rparen            = "\\)";
        sharp_lparen      = "#\\(";
        single_quote      = "'";
        backquote         = "`";
        comma             = ",";
        comma_at          = ",@";
        period            = ".";

        this->self
            +=  identifier
            |   boolean
            |   number
            |   character
            |   string
            |   lparen
            |   rparen
            |   sharp_lparen
            |   single_quote
            |   backquote
            |   comma
            |   comma_at
            |   period
            ;

        this->self( "WS" )
            =   intertoken_space
            ;
    }

    lex::token_def<> delimiter;
    lex::token_def<> intertoken_space;
    lex::token_def<> identifier;
    lex::token_def<> boolean;
    lex::token_def<> number;
    lex::token_def<> character;
    lex::token_def<> string;
    lex::token_def<> lparen;
    lex::token_def<> rparen;
    lex::token_def<> sharp_lparen;
    lex::token_def<> single_quote;
    lex::token_def<> backquote;
    lex::token_def<> comma;
    lex::token_def<> comma_at;
    lex::token_def<> period;

};  //  struct r5rs_tokens

}   //  namespace rose

#endif  //  __ROSE_R5RS_LEXER_HPP__
