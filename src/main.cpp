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

bool parse(std::string const& source, ast_program& program) {
    typedef
        std::string::const_iterator
        iterator_type;

    typedef
        rose::parser::intertoken_space<iterator_type>
        skipper_type;

    iterator_type first = source.begin();
    iterator_type last = source.end();

    typedef
        rose::parser::r5rs_grammar<iterator_type, skipper_type>
        r5rs_grammar;

    r5rs_grammar grammar;
    skipper_type skipper;

    bool match = qi::phrase_parse(first, last, grammar, skipper, program);

    return match && first == last;
}

bool generate_program(ast_program const& program, std::string& output) {
    using ascii::space;
    using ascii::space_type;
    using karma::generate_delimited;

    typedef
        std::back_insert_iterator<std::string>
        iterator_type;

    output.clear();
    iterator_type sink(output);
    generator::program<iterator_type, space_type> grammar;

    return generate_delimited(sink, grammar, space, program);
}

void repl() {
    while (true) {
        std::string source;
        std::cout << cli_prompt;
        if (!std::getline(std::cin, source)) {
            break;
        }

        ast_program program;
        if (!parse(source, program)) {
            std::cerr << "error" << std::endl;
            continue;
        }

        std::string output;
        if (generate_program(program, output)) {
            std::cout << output << std::endl;
        }
        else {
            std::cerr << "error" << std::endl;
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
