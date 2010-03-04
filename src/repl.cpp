#include "rose/intertoken_space.hpp"
#include "rose/repl.hpp"
#include "rose/tokenizer.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace rose {

namespace qi = boost::spirit::qi;

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

    std::string
        default_prompt( "rose> " ),
        continue_prompt( " ...> " ),
        prompt = default_prompt,
        line,
        source;

    while( std::cout << prompt, std::getline( std::cin, line ) ) {
        source.append( line );
        iterator_type first = source.begin();
        iterator_type last = source.end();

        typedef
            rose::tokenizer<iterator_type, skipper_type>
            tokenizer;

        typedef
            std::back_insert_iterator<std::vector<std::string> >
            output_iterator_type;

        std::vector<std::string> tokens;
        output_iterator_type output_iterator( tokens );
        tokenizer grammar( output_iterator );
        skipper_type skipper;

        bool matched = qi::phrase_parse( first,last, grammar, skipper );
        bool full_matched = matched && first == last;

        if( full_matched ) {
            print_tokens( tokens.begin(), tokens.end() );
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
