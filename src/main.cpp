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

void parse_and_generate(std::string const& input) {
    ast_program program;
    std::string output;

    parse(input, program) && generate_program(program, output) ?
        std::cout << output << std::endl
      : std::cerr << "error" << std::endl;
}

void do_repl(std::string const& prompt) {
    for (std::string input;
            (std::cout << prompt), std::getline(std::cin, input);)
    {
        parse_and_generate(input);
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
    parse_and_generate(load_file(input_file));
}

}   //  namespace rose

/// Default REPL prompt.
static const std::string DEFAULT_REPL_PROMPT("rose> ");

int main(int argc, char* argv[]) try {
    using boost::program_options::command_line_parser;
    using boost::program_options::notify;
    using boost::program_options::options_description;
    using boost::program_options::positional_options_description;
    using boost::program_options::store;
    using boost::program_options::value;
    using boost::program_options::variables_map;

    std::string repl_prompt;
    std::vector<std::string> input_files;

    options_description generic_options("Generic command line options");
    generic_options.add_options()
        ("help,h",
         "Show this help message.")

        ("prompt,p",
         value(&repl_prompt)->default_value(DEFAULT_REPL_PROMPT),
         "Set the prompt string of the REPL environment.")
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
      : rose::do_repl(repl_prompt);

    return 0;
}
catch(std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
}
