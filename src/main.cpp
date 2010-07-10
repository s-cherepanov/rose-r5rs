#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"

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

const std::string cli_prompt("rose> ");

boost::optional<std::string> generate_program(ast_program const& program) {
    using ascii::space;
    using ascii::space_type;
    using karma::generate_delimited;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    boost::optional<std::string> result;

    std::string output;
    iterator_type sink(output);
    generator::program<iterator_type, space_type> grammar;
    if (generate_delimited(sink, grammar, space, program)) {
        result.reset(output);
    }

    return result;
}

void repl() {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    std::string source;

    while (std::cout << cli_prompt, std::getline(std::cin, source)) {
        iterator_type first = source.begin();
        iterator_type last = source.end();

        typedef
            rose::parser::r5rs_grammar<iterator_type, skipper_type>
            r5rs_grammar;

        r5rs_grammar grammar;
        skipper_type skipper;
        ast_program program;

        bool match = qi::phrase_parse(
                first, last, grammar, skipper, program);
        bool full_match = match && first == last;

        if (!full_match) {
            std::cerr << "error" << std::endl;
        }
        else {
            std::cout << "ok" << std::endl;
            boost::optional<std::string> output = generate_program(program);
            if (output) {
                std::cout << *output << std::endl;
            }
            else {
                std::cout << "failed to generate code" << std::endl;
            }
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
