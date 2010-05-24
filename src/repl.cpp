#include "rose/intertoken_space.hpp"
#include "rose/repl.hpp"
#include "rose/r5rs_grammar.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>

namespace rose {

namespace qi = boost::spirit::qi;

const std::string default_prompt("rose> ");

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

    while (std::cout << prompt, std::getline(std::cin, line)) {
        source.append(line);
        iterator_type first = source.begin();
        iterator_type last = source.end();

        typedef
            rose::r5rs_grammar<iterator_type, skipper_type>
            r5rs_grammar;

        r5rs_grammar grammar;
        skipper_type skipper;

        bool match = qi::phrase_parse(first,last, grammar, skipper);
        bool full_match = match && first == last;

        source.clear();

        if (!full_match) {
            std::cerr << "error" << std::endl;
        }
    }
}

}   //  namespace rose
