#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/gc/handle.hpp"
#include "rose/parser/intertoken_space.hpp"
#include "rose/parser/program.hpp"
#include "rose/value.hpp"

#include <boost/format.hpp>
#include <boost/spirit/include/qi.hpp>

#include <algorithm>
#include <fstream>

namespace rose {

namespace qi = boost::spirit::qi;

environment_ptr build_initial_env();

void call_evaluator(std::string const& input, environment_ptr env) {
    evaluator i(env);

    if (!i.parse(input)) {
        std::cout << "ABORT: syntax error" << std::endl;
    }

    gc::handle<value> result = i.eval();
    if (!!result) {
        std::cout << "=> " << result << std::endl;
    }
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
    environment_ptr env(build_initial_env());

    while (true) {
        std::cout << format_prompt(prompt) % line_no++;

        if (!std::getline(std::cin, input)) {
            break;
        }

        call_evaluator(input, env);
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
    call_evaluator(load_file(input_file), build_initial_env());
}

}   //  namespace rose
