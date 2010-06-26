#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"
#include "rose/repl.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace rose {

namespace ascii = boost::spirit::ascii;
namespace karma = boost::spirit::karma;
namespace qi = boost::spirit::qi;

const std::string default_prompt("rose> ");

std::string generate_program(ast::program const& program) {
    using ascii::space;
    using ascii::space_type;
    using karma::generate_delimited;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    std::string output;
    iterator_type sink(output);
    generator::program<iterator_type, space_type> grammar;
    generate_delimited(sink, grammar, space, program);

    return output;
}

void repl() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    std::string prompt = default_prompt;
    std::string line;
    std::string source;

    while (std::cout << prompt, std::getline(std::cin, line)) {
        source.append(line);
        iterator_type first = source.begin();
        iterator_type last = source.end();

        typedef
            rose::parser::r5rs_grammar<iterator_type, skipper_type>
            r5rs_grammar;

        r5rs_grammar grammar;
        skipper_type skipper;
        ast::program program;

        bool match = qi::phrase_parse(
                first, last, grammar, skipper, program);
        bool full_match = match && first == last;

        source.clear();

        if (!full_match) {
            std::cerr << "error" << std::endl;
        }
        else {
            std::cout << generate_program(program) << std::endl;
        }
    }
}

}   //  namespace rose

int main(int argc, char** argv) try {
    rose::repl();
    return 0;
}
catch(std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
}
