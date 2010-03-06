#include "rose/intertoken_space.hpp"
#include "rose/repl.hpp"
#include "rose/r5rs_grammar.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace rose {

namespace qi = boost::spirit::qi;

const std::string default_prompt( "rose> " );
const std::string continue_prompt( " ...> " );

template<typename Iterator>
void print_tokens( Iterator first, Iterator last ) {
    for( std::cout << "{" << *first++ << "}"; first != last; ) {
        std::cout << " {" << *first++ << "}";
    }
    std::cout << std::endl;
}

void repl() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::intertoken_space<iterator_type>
        skipper_type;

    std::string prompt = default_prompt;
    std::string line;
    std::string source;

    while( std::cout << prompt, std::getline( std::cin, line ) ) {
        source.append( line );
        iterator_type first = source.begin();
        iterator_type last = source.end();

        typedef
            rose::r5rs_grammar<iterator_type, skipper_type>
            r5rs_grammar;

        r5rs_grammar grammar;
        skipper_type skipper;

        bool match = qi::phrase_parse( first,last, grammar, skipper );
        bool full_match = match && first == last;

        if( full_match ) {
            source.clear();
            prompt = default_prompt;
        }
        else {
            source.push_back( '\n' );
            prompt = continue_prompt;
        }
    }

    std::cout << "; EXIT" << std::endl;
}

}   //  namespace rose
