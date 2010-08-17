#include "rose/environment.hpp"
#include "rose/gc/handle.hpp"
#include "rose/generator/program.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/program.hpp"
#include "rose/value.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <fstream>

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
        rose::parser::program<iterator_type, skipper_type>
        program_parser;

    program_parser parser;
    skipper_type skipper;

    bool match = qi::phrase_parse(first, last, parser, skipper, program);

    return match && first == last;
}

bool generate(ast_program const& program, std::string& output) {
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

environment_ptr build_initial_env() {
    return environment_ptr(new environment);
}

gc::handle<value> evaluate_program(
        ast_program const& program, environment_ptr env);

void parse_and_generate(std::string const& input, environment_ptr env) {
    ast_program program;
    std::string output;

    parse(input, program) && generate(program, output) ?
        std::cout << output << std::endl
      : std::cerr << "error" << std::endl;

    evaluate_program(program, env);
}

boost::format format_prompt(std::string const& prompt) {
    boost::format formatter(prompt);

    formatter.exceptions(
            boost::io::all_error_bits ^
            (boost::io::too_many_args_bit |
             boost::io::too_few_args_bit));

    return formatter;
}

void do_repl(std::string const& prompt) {
    std::string input;
    int line_no = 0;
    environment_ptr env = build_initial_env();

    while (std::cout << format_prompt(prompt) % line_no++,
            std::getline(std::cin, input))
    {
        parse_and_generate(input, env);
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
    parse_and_generate(load_file(input_file), build_initial_env());
}

}   //  namespace rose
