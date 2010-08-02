#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/r5rs_grammar.hpp"

#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <fstream>
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

void do_repl() {
    for (std::string source;
            (std::cout << cli_prompt),
            std::getline(std::cin, source);)
    {
        ast_program program;
        std::string output;

        if (parse(source, program) && generate_program(program, output)) {
            std::cout << output << std::endl;
        }
        else {
            std::cerr << "error" << std::endl;
        }
    }
}

std::string load_file(std::string const& filename) {
    std::ifstream in(filename.c_str());

    if (!in.is_open()) {
        std::ostringstream out;
        out << "Couldn't open file: " << filename;
        throw std::runtime_error(out.str());
    }

    in.unsetf(std::ios::skipws);
    return std::string(
            std::istreambuf_iterator<char>(in.rdbuf()),
            std::istreambuf_iterator<char>());
}

void do_batch(std::string const& input_file) {
    ast_program program;
    if (!parse(load_file(input_file), program)) {
        std::cerr << "error" << std::endl;
        return;
    }

    std::string output;
    if (generate_program(program, output)) {
        std::cout << output << std::endl;
    }
    else {
        std::cerr << "error" << std::endl;
    }
}

}   //  namespace rose

int main(int argc, char* argv[]) try {
    using boost::program_options::command_line_parser;
    using boost::program_options::notify;
    using boost::program_options::options_description;
    using boost::program_options::positional_options_description;
    using boost::program_options::store;
    using boost::program_options::value;
    using boost::program_options::variables_map;

    std::vector<std::string> input_files;

    options_description generic_options("Generic command line options");
    generic_options.add_options()
        ("help,h",
         "Show this help message.")
        ;

    options_description hidden_options;
    hidden_options.add_options()
        ("input-file",
         value<std::vector<std::string> >(&input_files),
         "Input source file.")
        ;

    options_description cmdline_options;
    cmdline_options
        .add(generic_options)
        .add(hidden_options);

    positional_options_description positional_options;
    positional_options.add("input-file", 1);

    variables_map cmdline_vm;
    store(
            command_line_parser(argc, argv)
            .options(cmdline_options)
            .positional(positional_options)
            .run(),
            cmdline_vm
    );
    notify(cmdline_vm);

    if (cmdline_vm.count("help")) {
        std::cout << "Usage: rose <script-file> | [options]\n" << std::endl;
        std::cout << generic_options << std::endl;
        return 0;
    }

    cmdline_vm.count("input-file") ?
        rose::do_batch(input_files[0])
      : rose::do_repl();

    return 0;
}
catch(std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
}
