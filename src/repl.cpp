#include "rose/intertoken_space.hpp"
#include "rose/r5rs_grammar.hpp"
#include "rose/repl.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>

namespace rose {

namespace qi = boost::spirit::qi;

void repl() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::intertoken_space<iterator_type>
        skipper_type;

    typedef
        rose::r5rs_grammar<iterator_type, skipper_type>
        r5rs_grammar;

    std::string source;

    std::string
        default_prompt( "rose> " ),
        continue_prompt( "  ... " ),
        prompt = default_prompt,
        line;

    while( std::cout << prompt, std::getline( std::cin, line ) ) {
        source.append( line );

        r5rs_grammar grammar;
        skipper_type skipper;
        iterator_type first = source.begin();
        iterator_type last = source.end();

        bool matched = qi::phrase_parse( first,last, grammar, skipper );
        bool full_matched = matched && first == last;

        if( full_matched ) {
            source.clear();
            prompt = default_prompt;
        }
        else {
            std::cout
                <<  boost::format( "[%1%]" )
                    % source
                << std::endl;
            source.push_back( '\n' );
            prompt = continue_prompt;
        }
    }

    std::cout << "; EXIT" << std::endl;
}

}   //  namespace rose
