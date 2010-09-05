#include "rose/environment.hpp"
#include "rose/evaluator.hpp"
#include "rose/exception.hpp"
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

        gc::handle<value> result = evaluator(env).eval(input);
        if (!is_none(result)) {
            std::cout << "=> " << result << std::endl;
        }
    }
}

std::string load_file(std::string const& filename) {
    std::ifstream in(filename.c_str());

    if (!in.is_open()) {
        BOOST_THROW_EXCEPTION(
                file_not_found()
                << boost::errinfo_file_name(filename));
    }

    in.unsetf(std::ios::skipws);
    return std::string(
            std::istreambuf_iterator<char>(in.rdbuf()),
            std::istreambuf_iterator<char>());
}

void do_batch(std::string const& input_file) {
    evaluator(build_initial_env()).eval(load_file(input_file));
}

}   //  namespace rose
